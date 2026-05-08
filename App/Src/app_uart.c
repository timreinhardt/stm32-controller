/* app_uart.c
 * UART interface
 * - Serial RX/TX
 * - Command input
 * - UART processing
 */
#include "app_uart.h"
#include "app_uart_cmd.h"

#include <ctype.h>
#include <stdint.h>
#include <string.h>

#ifndef UNIT_TEST
#include "main.h"
extern UART_HandleTypeDef huart2;
#endif

#ifdef UNIT_TEST

#define HAL_OK 0
#define HAL_ERROR 1
#define HAL_MAX_DELAY 0

#define GPIO_PIN_SET 1
#define GPIO_PIN_RESET 0

#define BOARD_STATUS_LED_PORT 0
#define BOARD_STATUS_LED_PIN  0

#define HAL_UART_Transmit(...)   ((void)0)
#define HAL_UART_Receive(...)    (HAL_ERROR)
#define HAL_GPIO_WritePin(...)   ((void)0)
#define HAL_GPIO_TogglePin(...)  ((void)0)

#else

#define BOARD_STATUS_LED_PORT   LD2_GPIO_Port
#define BOARD_STATUS_LED_PIN    LD2_Pin

#endif

#define UART_RX_BUFFER_SIZE 64

static char rx_buffer[UART_RX_BUFFER_SIZE];
static unsigned int rx_index = 0;


static void App_UartSend(const char *text)
{
    HAL_UART_Transmit(
        &huart2,
        (uint8_t *)text,
        (uint16_t)strlen(text),
        HAL_MAX_DELAY
    );
}


void App_UartToUpper(char *text)
{
    while (*text != '\0')
    {
        *text = (char)toupper((unsigned char)*text);
        text++;
    }
}


App_UartCommand_t App_UartParseCommand(const char *cmd)
{
    App_UartCommand_t command_index;

    for (command_index = APP_UART_CMD_UNKNOWN + 1;
         command_index < APP_UART_CMD_COUNT;
         command_index++)
    {
        if (strcmp(cmd, APP_UART_CMD_TEXT[command_index]) == 0)
        {
            return command_index;
        }
    }

    return APP_UART_CMD_UNKNOWN;
}


static void App_UartExecuteCommand(App_UartCommand_t command)
{
    switch (command)
    {
        case APP_UART_CMD_PING:
            App_UartSend("PONG\r\n");
            break;

        case APP_UART_CMD_HELP:
            App_UartSend(
                "Commands: PING, HELP, STATUS, LED_ON, LED_OFF, LED_TOGGLE\r\n"
            );
            break;

        case APP_UART_CMD_STATUS:
            App_UartSend("STATUS: STM32 READY\r\n");
            break;

        case APP_UART_CMD_LED_ON:
            HAL_GPIO_WritePin(
                BOARD_STATUS_LED_PORT,
                BOARD_STATUS_LED_PIN,
                GPIO_PIN_SET
            );
            App_UartSend("LED ON OK\r\n");
            break;

        case APP_UART_CMD_LED_OFF:
            HAL_GPIO_WritePin(
                BOARD_STATUS_LED_PORT,
                BOARD_STATUS_LED_PIN,
                GPIO_PIN_RESET
            );
            App_UartSend("LED OFF OK\r\n");
            break;

        case APP_UART_CMD_LED_TOGGLE:
            HAL_GPIO_TogglePin(
                BOARD_STATUS_LED_PORT,
                BOARD_STATUS_LED_PIN
            );
            App_UartSend("LED TOGGLE OK\r\n");
            break;

        case APP_UART_CMD_UNKNOWN:
        default:
            App_UartSend("ERR: UNKNOWN COMMAND\r\n");
            break;
    }
}


static void App_UartProcessCommand(char *cmd)
{
    App_UartCommand_t command;

    App_UartToUpper(cmd);

    command = App_UartParseCommand(cmd);

    App_UartExecuteCommand(command);
}


void App_UartInit(void)
{
    App_UartSend("\r\nSTM32 UART READY\r\n");
    App_UartSend("Type HELP then press Enter\r\n");
}


void App_UartTask(void)
{
    uint8_t ch;

    if (HAL_UART_Receive(&huart2, &ch, 1, 0) != HAL_OK)
    {
        return;
    }

    if ((ch == '\r') || (ch == '\n'))
    {
        if (rx_index > 0)
        {
            rx_buffer[rx_index] = '\0';

            App_UartProcessCommand(rx_buffer);

            rx_index = 0;
        }

        return;
    }

    if (rx_index < (UART_RX_BUFFER_SIZE - 1))
    {
        rx_buffer[rx_index] = (char)ch;
        rx_index++;
    }
    else
    {
        rx_index = 0;

        App_UartSend("ERR: COMMAND TOO LONG\r\n");
    }
}
