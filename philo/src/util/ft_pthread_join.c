#include "../philo.h"

int ft_pthread_join(pthread_t th, void **value_ptr) {
    int ret;
    
    ret = pthread_join(th, value_ptr);
    if (ret != 0)
        printf("pthread_join: error\n");
    return ret;
}
