#include "app.h"
#include <stdio.h>

static int counter = 0;

int app_next_count(void)
{
    counter++;
    return counter;
}

void app_run_once(void)
{
    app_next_count();
}
