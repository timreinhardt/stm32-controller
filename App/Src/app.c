#include "app.h"
#include "app_state.h"

static int rate = 1000;

void app_reset(void)
{
    rate = 1000;
    app_state_init();
}

int app_get_rate(void)
{
    return rate;
}

const char *app_set_rate(int value)
{
    if (value < 0 || value > 5000) {
        return "ERR RANGE\r\n";
    }

    rate = value;
    return "OK\r\n";
}
