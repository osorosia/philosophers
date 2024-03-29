/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:32:37 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 17:06:21 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/time.h>
# include <unistd.h>

# ifndef DEBUG
#  define DEBUG 0
# endif

typedef enum e_action_kind {
	EAT,
	SLEEP,
	THINK,
	GET_FORK,
}	t_action_kind;

typedef struct s_rule		t_rule;
typedef struct s_philo		t_philo;
typedef struct s_table		t_table;
typedef struct s_monitor	t_monitor;

struct s_rule {
	long	philo_num;
	long	die;
	long	eat;
	long	sleep;
	long	eat_count;
};

struct s_philo {
	long			id;
	t_rule			*rule;
	t_table			*table;

	t_action_kind	next_act_kind;
	long			prev_eat_time;
	long			prev_act_time;
	long			eat_count;
};

struct s_table {
	t_philo			**philos;
	t_rule			*rule;

	pthread_mutex_t	*forks;
	pthread_mutex_t	*eat_time_mutex;
	pthread_mutex_t	*eat_count_mutex;
	pthread_mutex_t	print_mutex;

	long			start_time;

	bool			finish;
};

// action.c
bool	action(t_philo *philo, t_action_kind act_kind);

// monitor_routine.c
void	*monitor_routine(void *arg);

// philo_routine.c
void	*philo_routine(void *arg);

// print.c
bool	print_action(t_philo *philo, t_action_kind act_kind);

// table.c
t_table	*table_new(int argc, char **argv);
void	table_free(t_table *table);

//
// ft_pthread
// 
int		ft_pthread_create(pthread_t *th, const pthread_attr_t *attr, \
					  void *(*start_routine)(void *), void *arg);
int		ft_pthread_join(pthread_t th, void **value_ptr);
int		ft_pthread_mutex_destroy(pthread_mutex_t *mutex);
int		ft_pthread_mutex_lock(pthread_mutex_t *mutex);
int		ft_pthread_mutex_unlock(pthread_mutex_t *mutex);

//
// util
//
long	ft_atol(char *str);
void	*ft_calloc(size_t count, size_t size);
bool	ft_isdigit(char c);
long	get_timestamp(void);
bool	is_num(char *str);

#endif
