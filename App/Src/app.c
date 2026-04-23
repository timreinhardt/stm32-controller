#include "app.h"

static app_state_t state = APP_IDLE;
static int rate = 1000;

void app_reset(void)
{
    state = APP_IDLE;
    rate = 1000;
}

app_state_t app_get_state(void)
{
    return state;
}

int app_get_rate(void)
{
    return rate;
}

const char *app_start(void)
{
    if (state == APP_FAULT) {
        return "ERR FAULT\r\n";
    }

    state = APP_RUNNING;
    return "OK\r\n";
}

const char *app_stop(void)
{
    if (state == APP_FAULT) {
        return "ERR FAULT\r\n";
    }

    state = APP_IDLE;
    return "OK\r\n";
}

const char *app_fault(void)
{
    state = APP_FAULT;
    return "OK\r\n";
}

const char *app_clear_fault(void)
{
    state = APP_IDLE;
    return "OK\r\n";
}

const char *app_set_rate(int value)
{
    if (value < 0 || value > 5000) {
        return "ERR RANGE\r\n";
    }

    rate = value;
    return "OK\r\n";
}
