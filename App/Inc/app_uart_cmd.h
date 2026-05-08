/* App/Inc/app_uart_cmd.h */

#ifndef APP_UART_CMD_H
#define APP_UART_CMD_H

typedef enum
{
    APP_UART_CMD_UNKNOWN = 0,
    APP_UART_CMD_PING,
    APP_UART_CMD_HELP,
    APP_UART_CMD_STATUS,
    APP_UART_CMD_LED_ON,
    APP_UART_CMD_LED_OFF,
    APP_UART_CMD_LED_TOGGLE,
    APP_UART_CMD_COUNT

} App_UartCommand_t;


/*
 * Enum index matches text table index.
 * This keeps:
 * enum value ↔ readable command text
 */
static const char * const APP_UART_CMD_TEXT[APP_UART_CMD_COUNT] =
{
    "UNKNOWN",
    "PING",
    "HELP",
    "STATUS",
    "LED_ON",
    "LED_OFF",
    "LED_TOGGLE"
};

#endif // APP_UART_CMD_H
