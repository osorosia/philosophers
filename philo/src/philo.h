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
    DIE,
} t_action_kind;

typedef struct s_rule t_rule;
typedef struct s_philo t_philo;
typedef struct s_table t_table;
typedef struct s_monitor t_monitor;

struct s_rule {
    long philo_num;
    long die;
    long eat;
    long sleep;
    long times;
};

struct s_philo {
    long id;
    t_rule *rule;
    t_table *table;

    t_action_kind next_act_kind;
    long prev_eat_time;
    long prev_act_time;
    long eat_count;
};

struct s_table {
    long id;
    t_philo **philos;
    pthread_mutex_t *forks;
    pthread_mutex_t print_mutex;
    t_rule *rule;
    long start_time;

    bool finish;
};

struct s_monitor {
    t_table *table;
    t_rule *rule;
    t_philo **philos;
};

// action.c
void action(t_philo *philo, t_action_kind act_kind);

// routine.c
void *philo_routine(void *arg);
void *monitor_routine(void *arg);

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
