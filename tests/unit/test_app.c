#include <assert.h>
#include <stdio.h>
#include "../../Core/Inc/app.h"

int main(void)
{
    app_reset();

    assert(app_get_state() == APP_IDLE);
    assert(app_get_rate() == 1000);

    app_start();
    assert(app_get_state() == APP_RUNNING);

    app_stop();
    assert(app_get_state() == APP_IDLE);

    printf("App tests passed\n");
    return 0;
}
