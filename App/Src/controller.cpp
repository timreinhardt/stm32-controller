#include "controller.hpp"
#include "main.h"
#include "command_handler.hpp"
#include "serial_command_interface.hpp"

extern UART_HandleTypeDef huart2;

class Controller : public ICommandHandler {
public:
    Controller()
        : serial_(huart2, *this)
    {
    }

    void init()
    {
        setLed(false);

        serial_.init();
        serial_.send("Controller Init\r\n");
    }

    void update()
    {
        // ---------------------------------------------
        // UART command processing
        // ---------------------------------------------
        serial_.process();

        // ---------------------------------------------
        // Blue button toggles LED state on each press
        // ---------------------------------------------
        static GPIO_PinState lastButtonState = GPIO_PIN_SET;

        GPIO_PinState currentButtonState =
            HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

        // Detect falling edge: released -> pressed
        if (lastButtonState == GPIO_PIN_SET &&
            currentButtonState == GPIO_PIN_RESET) {

            ledState_ = !ledState_;
            setLed(ledState_);
        }

        lastButtonState = currentButtonState;

        // Debounce
        HAL_Delay(20);
    }

    void setLed(bool on) override
    {
        ledState_ = on;

        HAL_GPIO_WritePin(
            LD2_GPIO_Port,
            LD2_Pin,
            on ? GPIO_PIN_SET : GPIO_PIN_RESET
        );
    }

    void setPump(bool on) override
    {
        // Temporary placeholder:
        // Pump command uses LED until real pump GPIO exists.
        setLed(on);
    }

    void printStatus() override
    {
        if (ledState_) {
            serial_.send("STATUS: LED ON\r\n");
        } else {
            serial_.send("STATUS: LED OFF\r\n");
        }
    }

private:
    SerialCommandInterface serial_;
    bool ledState_ = false;
};

static Controller controller;

extern "C" void Controller_Init(void)
{
    controller.init();
}

extern "C" void Controller_Update(void)
{
    controller.update();
}
