#include "controller.hpp"
#include "main.h"
#include <cstdio>   // printf

class Controller {
public:
    void init() {
        // LED off initially
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

        // Startup debug
        printf("Controller Init\r\n");
    }

    void update() {
        // Read button state
        GPIO_PinState button = HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin);

        if (button == GPIO_PIN_RESET) {
            // Button pressed
            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);

            // Debug print
            printf("Button PRESSED -> LED ON\r\n");

        } else {
            // Button released
            HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);

            // Debug print
            printf("Button RELEASED -> LED OFF\r\n");
        }

        // Slow output so console isn’t flooded
        HAL_Delay(200);
    }
};

static Controller controller;

extern "C" void Controller_Init(void) {
    controller.init();
}

extern "C" void Controller_Update(void) {
    controller.update();
}
