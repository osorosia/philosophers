#include "philo.h"

void *start_routine(void *arg) {
    long i;

    i = 0;
    while (i < 10) {
        printf("%ld\n", i);
        i++;
        sleep(1);
    }
    return NULL;
}
