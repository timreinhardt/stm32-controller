/* app_hw.c
 * Hardware control
 * - Button input - to be polled
 * - LED output
 */
#include "app_hw.h"
#include "main.h"

#define DEBOUNCE_MS 20

// Board hardware names
#define BOARD_CMD_BUTTON_PORT   B1_GPIO_Port
#define BOARD_CMD_BUTTON_PIN    B1_Pin

#define BOARD_STATUS_LED_PORT   LD2_GPIO_Port
#define BOARD_STATUS_LED_PIN    LD2_Pin

// RESET button is hardware NRST.
// It resets the MCU directly and is not read in code.

// USER / blue button is active-low:
// Pressed  = GPIO_PIN_RESET
// Released = GPIO_PIN_SET
//
// Behaviour:
// Each valid button press toggles LED state once.
void App_ButtonLedHw(void)
{
    static GPIO_PinState last_button_state = GPIO_PIN_SET;
    static uint32_t last_change_time_ms = 0;
    static GPIO_PinState debounced_button_state = GPIO_PIN_SET;
    static GPIO_PinState led_state = GPIO_PIN_RESET;

    GPIO_PinState button_state = HAL_GPIO_ReadPin(
        BOARD_CMD_BUTTON_PORT,
        BOARD_CMD_BUTTON_PIN
    );

    uint32_t now_ms = HAL_GetTick();

    // Raw button changed: restart debounce timer
    if (button_state != last_button_state)
    {
        last_change_time_ms = now_ms;
        last_button_state = button_state;
    }

    // If stable long enough, accept new button state
    if ((now_ms - last_change_time_ms) >= DEBOUNCE_MS)
    {
        // New valid press event (released -> pressed)
        if ((button_state != debounced_button_state) &&
            (button_state == GPIO_PIN_RESET))
        {
            // Toggle LED state
            if (led_state == GPIO_PIN_RESET)
            {
                led_state = GPIO_PIN_SET;
            }
            else
            {
                led_state = GPIO_PIN_RESET;
            }

            // Write toggled LED state to board LED
            HAL_GPIO_WritePin(
                BOARD_STATUS_LED_PORT,
                BOARD_STATUS_LED_PIN,
                led_state
            );
        }

        debounced_button_state = button_state;
    }
}
