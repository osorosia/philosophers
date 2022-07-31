#include "philo.h"

void print_action(t_philo *philo, t_action_kind act_kind, long timestamp) {
    const char *act[] = {
        "is eating",
        "is sleeping",
        "is thinking",
        "has taken a fork",
        "died",
    };
    
    pthread_mutex_lock(&philo->table->print_mutex);
    if (philo->table->start_time == 0)
        philo->table->start_time = timestamp;

    printf("%ld %ld %s\n", timestamp - philo->table->start_time, philo->id, act[act_kind]);
    pthread_mutex_unlock(&philo->table->print_mutex);
}

void action_eat(t_philo *philo) {
    long timestamp = get_timestamp();
    print_action(philo, EAT, timestamp);
    philo->prev_act_time = timestamp;
    philo->prev_eat_time = timestamp;

}

void action_sleep(t_philo *philo) {
    long timestamp = get_timestamp();
    while (timestamp - philo->prev_act_time < philo->rule->eat) {
        timestamp = get_timestamp();
    }
    print_action(philo, SLEEP, timestamp);
    philo->prev_act_time = timestamp;
}

void action_think(t_philo *philo) {
    long timestamp = get_timestamp();
    while (timestamp - philo->prev_act_time < philo->rule->sleep) {
        timestamp = get_timestamp();
    }
    print_action(philo, THINK, timestamp);
}

void action_get_fork(t_philo *philo) {
    long timestamp = get_timestamp();
    print_action(philo, GET_FORK, timestamp);
}

void action_die(t_philo *philo) {
    long timestamp = get_timestamp();
    print_action(philo, DIE, timestamp);
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
