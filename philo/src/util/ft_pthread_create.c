#include "../philo.h"

int ft_pthread_create(pthread_t *th, const pthread_attr_t *attr,
                      void *(*start_routine)(void *), void *arg) {
    int ret;

    ret = pthread_create(th, attr, start_routine, arg);
    if (ret != 0)
        printf("pthread_create: error\n");
    return ret;
}
