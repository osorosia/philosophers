#include "../philo.h"

long get_timestamp() {
    struct timeval tv;

    gettimeofday(&tv, NULL);
    return tv.tv_sec;
}
