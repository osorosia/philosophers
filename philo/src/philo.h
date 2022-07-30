#ifndef PHILO_H
#define PHILO_H

#include <limits.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

#ifndef DEBUG
#define DEBUG 0
#endif

typedef enum e_action_kind {
    EAT,
    SLEEP,
    THINK,
    GET_FORK,
    DIED,
} t_action_kind;

typedef struct s_rule {
    long philo_num;
    long die;
    long eat;
    long sleep;
    long times;
} t_rule;

typedef struct s_philo {
    t_action_kind next_act_kind;
    long start_time;
    long prev_eat_time;
    long prev_act_time;
} t_philo;

typedef struct s_table {
    long id;
    t_philo **philos;
    pthread_mutex_t *forks;
    t_rule *rule;

    bool finish;
    // for debug
} t_table;

// action.c
void action_eat(t_table *table, long id);
void action_sleep(t_table *table, long id);
void action_think(t_table *table, long id);

// print.c
void print_act(t_table *table, long id, t_action_kind act_kind);

// routine.c
void *start_routine(void *arg);

// 
// philo
// 
void philo_set_next_act(t_philo *philo);

//
// util
//
void error(char *str);
long ft_atol(char *str);
bool ft_isdigit(char c);
long get_timestamp();
bool is_num(char *str);

#endif
