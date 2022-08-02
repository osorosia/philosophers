#include "philo.h"

bool print_action(t_philo *philo, t_action_kind act_kind) {
    const char *act[] = {
        "is eating", "is sleeping", "is thinking", "has taken a fork", "died",
    };

    pthread_mutex_lock(&philo->table->print_mutex);
    philo->prev_act_time = get_timestamp();
    if (philo->table->finish) {
        pthread_mutex_unlock(&philo->table->print_mutex);
        return false;
    }
    printf("%ld\t%ld %s\n", philo->prev_act_time - philo->table->start_time,
           philo->id + 1, act[act_kind]);
    pthread_mutex_unlock(&philo->table->print_mutex);
    return true;
}

bool action_eat(t_philo *philo) {
    long timestamp = get_timestamp();
    if (!print_action(philo, EAT))
        return false;

    pthread_mutex_lock(&philo->table->eat_time_mutex[philo->id]);
    philo->prev_eat_time = timestamp;
    pthread_mutex_unlock(&philo->table->eat_time_mutex[philo->id]);

    pthread_mutex_lock(&philo->table->eat_count_mutex[philo->id]);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->table->eat_count_mutex[philo->id]);
    return true;
}

bool action_sleep(t_philo *philo) {
    long timestamp = get_timestamp();
    while (timestamp - philo->prev_act_time < philo->rule->eat) {
        usleep(100);
        timestamp = get_timestamp();
    }
    return print_action(philo, SLEEP);
}

bool action_think(t_philo *philo) {
    long timestamp = get_timestamp();
    while (timestamp - philo->prev_act_time < philo->rule->sleep) {
        usleep(100);
        timestamp = get_timestamp();
    }
    return print_action(philo, THINK);
}

bool action_get_fork(t_philo *philo) {
    long timestamp = get_timestamp();
    return print_action(philo, GET_FORK);
}

bool action_die(t_philo *philo) {
    return print_action(philo, DIE);
}

bool action(t_philo *philo, t_action_kind act_kind) {
    if (act_kind == EAT)
        return action_eat(philo);
    else if (act_kind == SLEEP)
        return action_sleep(philo);
    else if (act_kind == THINK)
        return action_think(philo);
    else if (act_kind == GET_FORK)
        return action_get_fork(philo);
    else if (act_kind == DIE)
        return action_die(philo);
    return false;
}
