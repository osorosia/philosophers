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
        pthread_mutex_lock(&table->forks[first_fork(philo)]);
        action(philo, GET_FORK);
        pthread_mutex_lock(&table->forks[second_fork(philo)]);
        action(philo, GET_FORK);
        action(philo, EAT);
        action(philo, SLEEP);
        pthread_mutex_unlock(&table->forks[second_fork(philo)]);
        pthread_mutex_unlock(&table->forks[first_fork(philo)]);
        action(philo, THINK);
    }
    return NULL;
}

void *monitor_routine(void *arg) {
    t_monitor *monitor = (t_monitor *)arg;
    t_philo **philos = monitor->philos;
    t_rule *rule = monitor->rule;
    t_table *table = monitor->table;

    while (true) {
        long i = 0;
        bool eat_ok = true;
        while (i < rule->philo_num) {
            pthread_mutex_lock(&table->eat_count_mutex[i]);
            if (rule->eat_count > 0 && philos[i]->eat_count < rule->eat_count)
                eat_ok = false;
            pthread_mutex_unlock(&table->eat_count_mutex[i]);

            pthread_mutex_lock(&table->eat_time_mutex[i]);
            if (philos[i]->prev_eat_time == 0 &&
                    get_timestamp() - table->start_time >= rule->die ||
                philos[i]->prev_eat_time > 0 &&
                    get_timestamp() - philos[i]->prev_eat_time >= rule->die) {

                pthread_mutex_lock(&table->print_mutex);
                {
                    printf("%ld\t%ld died\n", get_timestamp() - table->start_time, i + 1);
                    long i = 0;
                    while (i < rule->philo_num) {
                        pthread_detach(monitor->philo_th[i]);
                        i++;
                    }
                }
                pthread_mutex_unlock(&table->print_mutex);
                return NULL;
            }
            pthread_mutex_unlock(&table->eat_time_mutex[i]);

            i++;
        }
        if (eat_ok)
            break;
    }

    pthread_mutex_lock(&table->print_mutex);
    {
        long i = 0;
        while (i < rule->philo_num) {
            pthread_detach(monitor->philo_th[i]);
            i++;
        }
    }
    pthread_mutex_unlock(&table->print_mutex);
    return NULL;
}
