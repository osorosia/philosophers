#include "../philo.h"

void ft_pthread_mutex_destroy(pthread_mutex_t *mutex) {
    int ret;

    ret = pthread_mutex_destroy(mutex);
    if (ret != 0)
        printf("pthread_mutex_destroy: error\n");
}
