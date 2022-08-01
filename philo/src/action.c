#include "philo.h"

void print_action(t_philo *philo, t_action_kind act_kind) {
    const char *act[] = {
        "is eating",
        "is sleeping",
        "is thinking",
        "has taken a fork",
        "died",
    };

    pthread_mutex_lock(&philo->table->print_mutex);
    philo->prev_act_time = get_timestamp();
    printf("%ld\t%ld %s\n",
        philo->prev_act_time - philo->table->start_time,
        philo->id + 1,
        act[act_kind]);
    pthread_mutex_unlock(&philo->table->print_mutex);
}

void action_eat(t_philo *philo) {
    long timestamp = get_timestamp();
    print_action(philo, EAT);

    pthread_mutex_lock(&philo->table->eat_time_mutex[philo->id]);
    philo->prev_eat_time = timestamp;
    pthread_mutex_unlock(&philo->table->eat_time_mutex[philo->id]);

    pthread_mutex_lock(&philo->table->eat_count_mutex[philo->id]);
    philo->eat_count++;
    pthread_mutex_unlock(&philo->table->eat_count_mutex[philo->id]);
}

void action_sleep(t_philo *philo) {
    long timestamp = get_timestamp();
    while (timestamp - philo->prev_act_time < philo->rule->eat)
        timestamp = get_timestamp();
    print_action(philo, SLEEP);
}

void action_think(t_philo *philo) {
    long timestamp = get_timestamp();
    while (timestamp - philo->prev_act_time < philo->rule->sleep) {
        timestamp = get_timestamp();
    }
    print_action(philo, THINK);
}

void action_get_fork(t_philo *philo) {
    long timestamp = get_timestamp();
    print_action(philo, GET_FORK);
}

void action_die(t_philo *philo) {
    print_action(philo, DIE);
}

void action(t_philo *philo, t_action_kind act_kind) {
    if (act_kind == EAT)
        action_eat(philo);
    else if (act_kind == SLEEP)
        action_sleep(philo);
    else if (act_kind == THINK)
        action_think(philo);
    else if (act_kind == GET_FORK)
        action_get_fork(philo);
    else if (act_kind == DIE)
        action_die(philo);
}
