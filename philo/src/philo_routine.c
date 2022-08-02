#include "philo.h"

long first_fork(t_philo *philo) {
    long id;

    if (philo->id % 2 == 0)
        id = philo->id;
    else
        id = philo->id - 1;
    if (id < 0)
        id = philo->rule->philo_num - 1;
    return id;
}

long second_fork(t_philo *philo) {
    long id;

    if (philo->id % 2 == 0)
        id = philo->id - 1;
    else
        id = philo->id;
    if (id < 0)
        id = philo->rule->philo_num - 1;
    return id;
}

void *philo_routine(void *arg) {
    t_philo *philo = (t_philo *)arg;
    t_rule *rule = philo->rule;
    t_table *table = philo->table;

    while (true) {
        ft_pthread_mutex_lock(&table->forks[first_fork(philo)]);
        if (!action(philo, GET_FORK))
            break;
        ft_pthread_mutex_lock(&table->forks[second_fork(philo)]);
        if (!action(philo, GET_FORK) || !action(philo, EAT) ||
            !action(philo, SLEEP))
            break;
        ft_pthread_mutex_unlock(&table->forks[second_fork(philo)]);
        ft_pthread_mutex_unlock(&table->forks[first_fork(philo)]);
        if (!action(philo, THINK))
            break;
    }
    return NULL;
}
