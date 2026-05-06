#pragma once

#include "main.h"
#include "command_handler.hpp"
#include <cstddef>
#include <cstdint>

class SerialCommandInterface {
public:
    SerialCommandInterface(UART_HandleTypeDef& huart, ICommandHandler& handler);

    void init();
    void process();
    void send(const char* text);

private:
    UART_HandleTypeDef& huart_;
    ICommandHandler& handler_;

    char rxChar_ = 0;
    char line_[64] = {};
    std::size_t index_ = 0;

    void handleLine(const char* line);
};
