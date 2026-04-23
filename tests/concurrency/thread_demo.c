#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct
{
    int count;
    bool data_ready;
    pthread_mutex_t lock;
    pthread_cond_t cond;
} app_shared_t;

static app_shared_t app = {
    .count = 0,
    .data_ready = false,
    .lock = PTHREAD_MUTEX_INITIALIZER,
    .cond = PTHREAD_COND_INITIALIZER
};

void *producer_thread(void *arg)
{
    (void)arg;

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&app.lock);

        app.count++;
        app.data_ready = true;
        printf("[producer] count updated to %d\n", app.count);

        pthread_cond_signal(&app.cond);
        pthread_mutex_unlock(&app.lock);

        sleep(1);
    }

    return NULL;
}

void *consumer_thread(void *arg)
{
    (void)arg;

    for (int i = 0; i < 5; i++) {
        pthread_mutex_lock(&app.lock);

        while (!app.data_ready) {
            pthread_cond_wait(&app.cond, &app.lock);
        }

        printf("[consumer] observed count = %d\n", app.count);
        app.data_ready = false;

        pthread_mutex_unlock(&app.lock);
    }

    return NULL;
}

int main(void)
{
    pthread_t t1, t2;

    if (pthread_create(&t1, NULL, producer_thread, NULL) != 0) {
        perror("pthread_create producer");
        return 1;
    }

    if (pthread_create(&t2, NULL, consumer_thread, NULL) != 0) {
        perror("pthread_create consumer");
        return 1;
    }

    pthread_join(t1, NULL);
    pthread_join(t2, NULL);

    pthread_mutex_destroy(&app.lock);
    pthread_cond_destroy(&app.cond);

    return 0;
}
