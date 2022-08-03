/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:38:44 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 15:19:10 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

long	first_fork(t_philo *philo)
{
	long	id;

	if (philo->id % 2 == 0)
		id = philo->id;
	else
		id = philo->id - 1;
	if (id < 0)
		id = philo->rule->philo_num - 1;
	return (id);
}

long	second_fork(t_philo *philo)
{
	long	id;

	if (philo->id % 2 == 0)
		id = philo->id - 1;
	else
		id = philo->id;
	if (id < 0)
		id = philo->rule->philo_num - 1;
	return (id);
}

void	*one_philo_routine(t_philo *philo)
{
	t_table	*table;
	bool	is_finish;

	table = philo->table;
	is_finish = false;
	ft_pthread_mutex_lock(&table->forks[first_fork(philo)]);
	action(philo, GET_FORK);
	while (!is_finish)
	{
		ft_pthread_mutex_lock(&table->print_mutex);
		is_finish = table->finish;
		ft_pthread_mutex_unlock(&table->print_mutex);
		usleep(100);
	}
	ft_pthread_mutex_unlock(&table->forks[first_fork(philo)]);
	return (NULL);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	t_table	*table;
	bool	is_finish;

	philo = (t_philo *)arg;
	if (philo->rule->philo_num == 1)
		return (one_philo_routine(philo));
	table = philo->table;
	is_finish = false;
	while (!is_finish)
	{
		ft_pthread_mutex_lock(&table->forks[first_fork(philo)]);
		if (!is_finish && !action(philo, GET_FORK))
			is_finish = true;
		ft_pthread_mutex_lock(&table->forks[second_fork(philo)]);
		if (!is_finish && !action(philo, GET_FORK)
			|| !is_finish && !action(philo, EAT)
			|| !is_finish && !action(philo, SLEEP))
			is_finish = true;
		ft_pthread_mutex_unlock(&table->forks[second_fork(philo)]);
		ft_pthread_mutex_unlock(&table->forks[first_fork(philo)]);
		if (!is_finish && !action(philo, THINK))
			is_finish = true;
	}
	return (NULL);
}
