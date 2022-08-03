/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:28:50 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:42:49 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	action_eat(t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp();
	if (!print_action(philo, EAT))
		return (false);
	ft_pthread_mutex_lock(&philo->table->eat_time_mutex[philo->id]);
	philo->prev_eat_time = timestamp;
	ft_pthread_mutex_unlock(&philo->table->eat_time_mutex[philo->id]);
	ft_pthread_mutex_lock(&philo->table->eat_count_mutex[philo->id]);
	philo->eat_count++;
	ft_pthread_mutex_unlock(&philo->table->eat_count_mutex[philo->id]);
	return (true);
}

bool	action_sleep(t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp();
	while (timestamp - philo->prev_act_time < philo->rule->eat)
	{
		usleep(100);
		timestamp = get_timestamp();
	}
	return (print_action(philo, SLEEP));
}

bool	action_think(t_philo *philo)
{
	long	timestamp;

	timestamp = get_timestamp();
	while (timestamp - philo->prev_act_time < philo->rule->sleep)
	{
		usleep(100);
		timestamp = get_timestamp();
	}
	return (print_action(philo, THINK));
}

bool	action_get_fork(t_philo *philo)
{
	return (print_action(philo, GET_FORK));
}

bool	action(t_philo *philo, t_action_kind act_kind)
{
	if (act_kind == EAT)
		return (action_eat(philo));
	else if (act_kind == SLEEP)
		return (action_sleep(philo));
	else if (act_kind == THINK)
		return (action_think(philo));
	else if (act_kind == GET_FORK)
		return (action_get_fork(philo));
	return (false);
}
