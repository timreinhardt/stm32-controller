#include <assert.h>
#include <stdio.h>
#include <string.h>

#include "../../App/Inc/app_uart.h"


static void Test_ToUpper(void)
{
    char test1[] = "ping";
    char test2[] = "Led_Toggle";

    App_UartToUpper(test1);
    App_UartToUpper(test2);

    assert(strcmp(test1, "PING") == 0);
    assert(strcmp(test2, "LED_TOGGLE") == 0);
}


static void Test_ParseCommand(void)
{
    char cmd1[] = "ping";
    char cmd2[] = "Led_On";
    char cmd3[] = "bad_cmd";

    App_UartToUpper(cmd1);
    App_UartToUpper(cmd2);
    App_UartToUpper(cmd3);

    assert(App_UartParseCommand(cmd1) == APP_UART_CMD_PING);
    assert(App_UartParseCommand("HELP") == APP_UART_CMD_HELP);
    assert(App_UartParseCommand("STATUS") == APP_UART_CMD_STATUS);

    assert(App_UartParseCommand(cmd2) == APP_UART_CMD_LED_ON);
    assert(App_UartParseCommand("LED_OFF") == APP_UART_CMD_LED_OFF);
    assert(App_UartParseCommand("LED_TOGGLE") == APP_UART_CMD_LED_TOGGLE);

    assert(App_UartParseCommand(cmd3) == APP_UART_CMD_UNKNOWN);
}


static void Test_CommandTextTable(void)
{
    assert(strcmp(APP_UART_CMD_TEXT[APP_UART_CMD_UNKNOWN], "UNKNOWN") == 0);
    assert(strcmp(APP_UART_CMD_TEXT[APP_UART_CMD_PING], "PING") == 0);
    assert(strcmp(APP_UART_CMD_TEXT[APP_UART_CMD_LED_TOGGLE], "LED_TOGGLE") == 0);
}


int main(void)
{
    Test_ToUpper();
    Test_ParseCommand();
    Test_CommandTextTable();

    printf("PASS: UART command unit tests\n");

    return 0;
}
