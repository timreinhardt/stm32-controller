#include "app_cmd.h"
#include "app.h"
#include "app_state.h"
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
        return app_state_handle_event(APP_EVENT_START);
    }

    if (strcmp(input, "STOP") == 0) {
        return app_state_handle_event(APP_EVENT_STOP);
    }

    if (strcmp(input, "FAULT") == 0) {
        return app_state_handle_event(APP_EVENT_FAULT_DETECTED);
    }

    if (strcmp(input, "RESET") == 0) {
        return app_state_handle_event(APP_EVENT_RESET);
    }

    if (sscanf(input, "SET RATE %d", &value) == 1) {
        return app_set_rate(value);
    }

    if (strcmp(input, "STATUS") == 0) {
        snprintf(buf, sizeof(buf), "STATUS %s RATE %d\r\n",
                 app_state_name(app_state_get()), app_get_rate());
        return buf;
    }

    return "ERR\r\n";
}
