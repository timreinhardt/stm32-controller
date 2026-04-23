#ifndef APP_H
#define APP_H

typedef enum
{
    APP_IDLE = 0,
    APP_RUNNING,
    APP_FAULT
} app_state_t;

void app_reset(void);
app_state_t app_get_state(void);
int app_get_rate(void);

const char *app_start(void);
const char *app_stop(void);
const char *app_fault(void);
const char *app_clear_fault(void);
const char *app_set_rate(int value);

#endif
