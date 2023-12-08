#include <stdlib.h>
#include <pthread.h>

void *increment_and_sleep(void *arg);

void costly_addition(int num)
{
    pthread_t array_id[num];

    for(int i = 0; i < num; ++i) {
        pthread_create(&array_id[i], NULL, increment_and_sleep, NULL);
    }

    for(int i = 0; i < num; ++i) {
        pthread_join(array_id[i], NULL);
    }
}
