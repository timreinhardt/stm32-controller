#include <stdio.h>
#include <stdbool.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>

#define TEST_LOOPS                 20

// Timing config (easy to understand at first glance)
#define PRODUCER_SLEEP_US         10000   // Producer updates every 10 ms
#define CONSUMER_TIMEOUT_FACTOR      10   // Consumer waits 10x producer delay
#define CONSUMER_TIMEOUT_US (PRODUCER_SLEEP_US * CONSUMER_TIMEOUT_FACTOR)

typedef struct
{
    pthread_mutex_t lock;
    pthread_cond_t  cond;

    int  count;
    bool data_ready;

    int producer_count;
    int consumer_count;

} app_t;

static app_t app;

// Convert microseconds to absolute timeout for pthread_cond_timedwait()
static struct timespec consumer_timeout_from_now(void)
{
    struct timespec timeout;

    timespec_get(&timeout, TIME_UTC);

    timeout.tv_sec  += CONSUMER_TIMEOUT_US / 1000000;
    timeout.tv_nsec += (CONSUMER_TIMEOUT_US % 1000000) * 1000;

    // Handle nanosecond overflow cleanly
    if (timeout.tv_nsec >= 1000000000L) {
        timeout.tv_sec++;
        timeout.tv_nsec -= 1000000000L;
    }

    return timeout;
}

// Producer = makes data + rings bell
void* producer_thread(void* arg)
{
    (void)arg;

    for (int i = 0; i < TEST_LOOPS; i++) {
        pthread_mutex_lock(&app.lock);

        app.count++;
        app.data_ready = true;
        app.producer_count++;
        printf("[producer] count updated to %d\n", app.count);
        pthread_cond_signal(&app.cond);
        pthread_mutex_unlock(&app.lock);

        usleep(PRODUCER_SLEEP_US);
    }

    return NULL;
}

// Consumer = sleeps until bell, reads data
void* consumer_thread(void* arg)
{
    (void)arg;

    for (int i = 0; i < TEST_LOOPS; i++) {
        pthread_mutex_lock(&app.lock);

        while (!app.data_ready) {
            struct timespec timeout = consumer_timeout_from_now();

            int rc = pthread_cond_timedwait(&app.cond, &app.lock, &timeout);

            if (rc == ETIMEDOUT) {
                printf("TEST FAIL: consumer timeout at loop %d\n", i);

                pthread_mutex_unlock(&app.lock);
                return NULL;
            }
        }

        printf("Consumer read count: %d\n", app.count);

        app.data_ready = false;
        app.consumer_count++;

        pthread_mutex_unlock(&app.lock);
    }

    return NULL;
}

int main(void)
{
    pthread_t producer;
    pthread_t consumer;

    app.count = 0;
    app.data_ready = false;
    app.producer_count = 0;
    app.consumer_count = 0;

    pthread_mutex_init(&app.lock, NULL);
    pthread_cond_init(&app.cond, NULL);

    pthread_create(&producer, NULL, producer_thread, NULL);
    pthread_create(&consumer, NULL, consumer_thread, NULL);

    pthread_join(producer, NULL);
    pthread_join(consumer, NULL);

    pthread_mutex_destroy(&app.lock);
    pthread_cond_destroy(&app.cond);

    if (app.producer_count == TEST_LOOPS &&
        app.consumer_count == TEST_LOOPS) {

        printf("TEST PASS: producer_count=%d consumer_reads=%d loops=%d\n",
               app.producer_count,
               app.consumer_count,
               TEST_LOOPS);
    } else {
        printf("TEST FAIL: producer_count=%d consumer_reads=%d loops=%d\n",
               app.producer_count,
               app.consumer_count,
               TEST_LOOPS);
    }

    return 0;
}
