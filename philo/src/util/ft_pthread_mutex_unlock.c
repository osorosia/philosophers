#include "../philo.h"

int ft_pthread_mutex_unlock(pthread_mutex_t *mutex) {
    int ret;
    
    ret = pthread_mutex_unlock(mutex);
    if (ret != 0)
        printf("pthread_mutex_unlock: error\n");
    return ret;
}
