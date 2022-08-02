#include "../philo.h"

int ft_pthread_mutex_lock(pthread_mutex_t *mutex) {
    int ret;
    
    ret = pthread_mutex_lock(mutex);
    if (ret != 0)
        printf("pthread_mutex_lock: error\n");
    return ret;
}
