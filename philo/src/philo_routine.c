/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_routine.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:38:44 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 18:15:47 by rnishimo         ###   ########.fr       */
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

void	init_sleep(t_philo *philo)
{
	if (philo->rule->philo_num % 2 == 0)
	{
		if (philo->id % 2 == 1)
			usleep(philo->rule->eat * 1000);
	}
	else
	{
		if (philo->id % 5 == 1)
			usleep(philo->rule->eat * 1000);
		else if (philo->id % 5 == 2)
			usleep(philo->rule->eat * 2000);
		else if (philo->id % 5 == 3)
			usleep(philo->rule->eat * 500);
		else if (philo->id % 5 == 4)
			usleep(philo->rule->eat * 1500);
	}
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;
	bool	is_finish;

	philo = (t_philo *)arg;
	if (philo->rule->philo_num == 1)
		return (one_philo_routine(philo));
	init_sleep(philo);
	is_finish = false;
	while (!is_finish)
	{
		ft_pthread_mutex_lock(&philo->table->forks[first_fork(philo)]);
		if (!is_finish && !action(philo, GET_FORK))
			is_finish = true;
		ft_pthread_mutex_lock(&philo->table->forks[second_fork(philo)]);
		if ((!is_finish && !action(philo, GET_FORK))
			|| (!is_finish && !action(philo, EAT))
			|| (!is_finish && !action(philo, SLEEP)))
			is_finish = true;
		ft_pthread_mutex_unlock(&philo->table->forks[second_fork(philo)]);
		ft_pthread_mutex_unlock(&philo->table->forks[first_fork(philo)]);
		if (!is_finish && !action(philo, THINK))
			is_finish = true;
	}
	return (NULL);
}
