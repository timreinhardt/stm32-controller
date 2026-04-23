#include "app_state.h"

static app_state_t current_state = APP_STATE_IDLE;

void app_state_init(void)
{
    current_state = APP_STATE_IDLE;
}

app_state_t app_state_get(void)
{
    return current_state;
}

const char *app_state_name(app_state_t state)
{
    switch (state) {
    	case APP_STATE_IDLE:
    		return "IDLE";
    	case APP_STATE_RUNNING:
    		return "RUNNING";
    	case APP_STATE_FAULT:
    		return "FAULT";
    	default:
    		return "UNKNOWN";
    }
}

const char *app_state_handle_event(app_event_t event)
{
    switch (current_state) {
    case APP_STATE_IDLE:
        switch (event) {

        case APP_EVENT_START:
            current_state = APP_STATE_RUNNING;
            return "OK\r\n";

        case APP_EVENT_FAULT_DETECTED:
            current_state = APP_STATE_FAULT;
            return "OK\r\n";

        case APP_EVENT_STOP:
        case APP_EVENT_RESET:
            return "OK\r\n";

        default:
            return "ERR\r\n";
        }

    case APP_STATE_RUNNING:

        switch (event) {

        case APP_EVENT_STOP:
            current_state = APP_STATE_IDLE;
            return "OK\r\n";

        case APP_EVENT_FAULT_DETECTED:
            current_state = APP_STATE_FAULT;
            return "OK\r\n";

        case APP_EVENT_START:
            return "OK\r\n";

        case APP_EVENT_RESET:
            return "ERR\r\n";

        default:
            return "ERR\r\n";
        }

    case APP_STATE_FAULT:
        switch (event) {
        case APP_EVENT_RESET:
            current_state = APP_STATE_IDLE;
            return "OK\r\n";
        case APP_EVENT_FAULT_DETECTED:
            return "OK\r\n";
        case APP_EVENT_START:
        case APP_EVENT_STOP:
            return "ERR FAULT\r\n";
        default:
            return "ERR\r\n";
        }

    default:
        return "ERR\r\n";
    }
}
