/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 14:00:45 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 14:07:18 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	print_action_eat(t_philo *philo, t_action_kind act_kind)
{
	const char	*act[] = {
		"is eating", "is sleeping", "is thinking", "has taken a fork",
	};

	ft_pthread_mutex_lock(&philo->table->eat_time_mutex[philo->id]);
	ft_pthread_mutex_lock(&philo->table->print_mutex);
	if (philo->table->finish)
	{
		ft_pthread_mutex_unlock(&philo->table->print_mutex);
		ft_pthread_mutex_unlock(&philo->table->eat_time_mutex[philo->id]);
		return (false);
	}
	philo->prev_act_time = get_timestamp();
	philo->prev_eat_time = philo->prev_act_time;
	printf("%ld\t%ld %s\n", philo->prev_act_time - philo->table->start_time,
		   philo->id + 1, act[act_kind]);
	ft_pthread_mutex_unlock(&philo->table->print_mutex);
	ft_pthread_mutex_unlock(&philo->table->eat_time_mutex[philo->id]);
	return (true);
}

bool	print_action(t_philo *philo, t_action_kind act_kind)
{
	const char	*act[] = {
		"is eating", "is sleeping", "is thinking", "has taken a fork",
	};

	if (act_kind == EAT)
		return (print_action_eat(philo, act_kind));
	ft_pthread_mutex_lock(&philo->table->print_mutex);
	if (philo->table->finish)
	{
		ft_pthread_mutex_unlock(&philo->table->print_mutex);
		return (false);
	}
	philo->prev_act_time = get_timestamp();
	printf("%ld\t%ld %s\n", philo->prev_act_time - philo->table->start_time,
		   philo->id + 1, act[act_kind]);
	ft_pthread_mutex_unlock(&philo->table->print_mutex);
	return (true);
}
