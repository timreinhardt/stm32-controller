#include "app_cmd.h"
#include "app.h"
#include <stdio.h>
#include <string.h>

const char *app_handle_command(const char *input)
{
    static char buf[64];
    int value;

    if (input == NULL) {
        return "ERR\r\n";
    }

    if (strcmp(input, "START") == 0) {
        return app_start();
    }

    if (strcmp(input, "STOP") == 0) {
        return app_stop();
    }

    if (strcmp(input, "FAULT") == 0) {
        return app_fault();
    }

    if (strcmp(input, "RESET") == 0) {
        return app_clear_fault();
    }

    if (sscanf(input, "SET RATE %d", &value) == 1) {
        return app_set_rate(value);
    }

    if (strcmp(input, "STATUS") == 0) {
        const char *state_str = "UNKNOWN";

        switch (app_get_state()) {
        case APP_IDLE:
            state_str = "IDLE";
            break;
        case APP_RUNNING:
            state_str = "RUNNING";
            break;
        case APP_FAULT:
            state_str = "FAULT";
            break;
        }

        snprintf(buf, sizeof(buf), "STATUS %s RATE %d\r\n", state_str, app_get_rate());
        return buf;
    }

    return "ERR\r\n";
}
