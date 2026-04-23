#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "../../Core/Inc/app.h"
#include "../../Core/Inc/app_cmd.h"

int main(void)
{
    app_reset();

    assert(strcmp(app_handle_command("STATUS"), "STATUS IDLE RATE 1000\r\n") == 0);

    assert(strcmp(app_handle_command("START"), "OK\r\n") == 0);
    assert(strcmp(app_handle_command("STATUS"), "STATUS RUNNING RATE 1000\r\n") == 0);

    assert(strcmp(app_handle_command("SET RATE 1500"), "OK\r\n") == 0);
    assert(strcmp(app_handle_command("STATUS"), "STATUS RUNNING RATE 1500\r\n") == 0);

    assert(strcmp(app_handle_command("FAULT"), "OK\r\n") == 0);
    assert(strcmp(app_handle_command("STATUS"), "STATUS FAULT RATE 1500\r\n") == 0);

    assert(strcmp(app_handle_command("START"), "ERR FAULT\r\n") == 0);
    assert(strcmp(app_handle_command("STOP"), "ERR FAULT\r\n") == 0);

    assert(strcmp(app_handle_command("RESET"), "OK\r\n") == 0);
    assert(strcmp(app_handle_command("STATUS"), "STATUS IDLE RATE 1500\r\n") == 0);

    assert(strcmp(app_handle_command("SET RATE 99999"), "ERR RANGE\r\n") == 0);
    assert(strcmp(app_handle_command("NOPE"), "ERR\r\n") == 0);

    printf("Command tests passed\n");
    return 0;
}
