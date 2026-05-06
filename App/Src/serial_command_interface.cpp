#include "serial_command_interface.hpp"
#include <cstring>

SerialCommandInterface::SerialCommandInterface(UART_HandleTypeDef& huart,
                                               ICommandHandler& handler)
    : huart_(huart),
      handler_(handler)
{
}

void SerialCommandInterface::init()
{
    send("CPP SERIAL READY\r\n");
    send("Type HELP then Enter\r\n");
}

void SerialCommandInterface::process()
{
    if (HAL_UART_Receive(&huart_, reinterpret_cast<uint8_t*>(&rxChar_), 1, 0) == HAL_OK) {
        if (rxChar_ == '\r' || rxChar_ == '\n') {
            if (index_ > 0) {
                line_[index_] = '\0';
                handleLine(line_);
                index_ = 0;
            }
            return;
        }

        if (index_ < sizeof(line_) - 1) {
            line_[index_++] = rxChar_;
        } else {
            index_ = 0;
            send("ERR: LINE TOO LONG\r\n");
        }
    }
}

void SerialCommandInterface::send(const char* text)
{
    HAL_UART_Transmit(
        &huart_,
        reinterpret_cast<uint8_t*>(const_cast<char*>(text)),
        std::strlen(text),
        HAL_MAX_DELAY
    );
}

void SerialCommandInterface::handleLine(const char* line)
{
    if (std::strcmp(line, "HELP") == 0) {
        send("Commands:\r\nHELP\r\nSTATUS\r\nLED ON\r\nLED OFF\r\nPUMP ON\r\nPUMP OFF\r\n");
    } else if (std::strcmp(line, "STATUS") == 0) {
        handler_.printStatus();
    } else if (std::strcmp(line, "LED ON") == 0) {
        handler_.setLed(true);
        send("OK: LED ON\r\n");
    } else if (std::strcmp(line, "LED OFF") == 0) {
        handler_.setLed(false);
        send("OK: LED OFF\r\n");
    } else if (std::strcmp(line, "PUMP ON") == 0) {
        handler_.setPump(true);
        send("OK: PUMP ON\r\n");
    } else if (std::strcmp(line, "PUMP OFF") == 0) {
        handler_.setPump(false);
        send("OK: PUMP OFF\r\n");
    } else {
        send("ERR: UNKNOWN COMMAND\r\n");
    }
}
