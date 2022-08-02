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
    long eat_count;
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
    pthread_mutex_t *eat_time_mutex;
    pthread_mutex_t *eat_count_mutex;
    pthread_mutex_t print_mutex;

    t_rule *rule;
    long start_time;

    bool finish;
};

struct s_monitor {
    t_table *table;
    t_rule *rule;
    t_philo **philos;

    pthread_t *philo_th;
};

// action.c
bool action(t_philo *philo, t_action_kind act_kind);

// monitor_routine.c
void *monitor_routine(void *arg);

// philo_routine.c
void *philo_routine(void *arg);

// table.c
t_table *table_new();
void table_free(t_table *table);

//
// util
//
void error(char *str);
long ft_atol(char *str);
void *ft_calloc(size_t count, size_t size);
bool ft_isdigit(char c);
int ft_pthread_create(pthread_t *th, const pthread_attr_t *attr,
                      void *(*start_routine)(void *), void *arg);
int ft_pthread_join(pthread_t th, void **value_ptr);
void ft_pthread_mutex_destroy(pthread_mutex_t *mutex);
int ft_pthread_mutex_lock(pthread_mutex_t *mutex);
int ft_pthread_mutex_unlock(pthread_mutex_t *mutex);
long get_timestamp();
bool is_num(char *str);

#endif
