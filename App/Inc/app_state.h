#ifndef APP_STATE_H
#define APP_STATE_H

typedef enum
{
    APP_STATE_IDLE = 0,
    APP_STATE_RUNNING,
    APP_STATE_FAULT
} app_state_t;

typedef enum
{
    APP_EVENT_NONE = 0,
    APP_EVENT_START,
    APP_EVENT_STOP,
    APP_EVENT_FAULT_DETECTED,
    APP_EVENT_RESET
} app_event_t;

void app_state_init(void);
app_state_t app_state_get(void);
const char *app_state_name(app_state_t state);
const char *app_state_handle_event(app_event_t event);

#endif
