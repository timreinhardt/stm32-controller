#include <assert.h>
#include <stdio.h>
#include <string.h>
#include "app.h"
#include "app_state.h"

int main(void)
{
    app_reset();
    assert(app_state_get() == APP_STATE_IDLE);
    assert(strcmp(app_state_handle_event(APP_EVENT_START), "OK\r\n") == 0);
    assert(app_state_get() == APP_STATE_RUNNING);

    app_reset();
    assert(app_state_get() == APP_STATE_IDLE);
    assert(strcmp(app_state_handle_event(APP_EVENT_STOP), "OK\r\n") == 0);
    assert(app_state_get() == APP_STATE_IDLE);

    app_reset();
    assert(strcmp(app_state_handle_event(APP_EVENT_FAULT_DETECTED), "OK\r\n") == 0);
    assert(app_state_get() == APP_STATE_FAULT);

    app_reset();
    app_state_handle_event(APP_EVENT_START);
    assert(app_state_get() == APP_STATE_RUNNING);
    assert(strcmp(app_state_handle_event(APP_EVENT_STOP), "OK\r\n") == 0);
    assert(app_state_get() == APP_STATE_IDLE);

    app_reset();
    app_state_handle_event(APP_EVENT_FAULT_DETECTED);
    assert(app_state_get() == APP_STATE_FAULT);
    assert(strcmp(app_state_handle_event(APP_EVENT_START), "ERR FAULT\r\n") == 0);
    assert(app_state_get() == APP_STATE_FAULT);

    app_reset();
    app_state_handle_event(APP_EVENT_FAULT_DETECTED);
    assert(strcmp(app_state_handle_event(APP_EVENT_RESET), "OK\r\n") == 0);
    assert(app_state_get() == APP_STATE_IDLE);

    printf("State matrix tests passed\n");
    return 0;
}
