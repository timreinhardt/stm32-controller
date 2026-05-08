#ifndef APP_UART_H
#define APP_UART_H

#include "app_uart_cmd.h"

void App_UartInit(void);
void App_UartTask(void);

/* Unit-testable helpers */
void App_UartToUpper(char *text);
App_UartCommand_t App_UartParseCommand(const char *cmd);

#endif // APP_UART_H
