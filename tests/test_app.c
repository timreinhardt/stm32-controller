#include <assert.h>
#include <stdio.h>
#include "../Core/Inc/app.h"

int main(void)
{
    assert(app_next_count() == 1);
    assert(app_next_count() == 2);
    assert(app_next_count() == 3);

    printf("All tests passed\n");
    return 0;
}
