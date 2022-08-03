/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitor_routine.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 11:11:12 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 11:47:35 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	set_finish(t_table *table)
{
	ft_pthread_mutex_lock(&table->print_mutex);
	table->finish = true;
	ft_pthread_mutex_unlock(&table->print_mutex);
}

long	get_eat_count_of_philo(t_table *table, long id)
{
	long	eat_count;

	ft_pthread_mutex_lock(&table->eat_count_mutex[id]);
	eat_count = table->philos[id]->eat_count;
	ft_pthread_mutex_unlock(&table->eat_count_mutex[id]);
	return (eat_count);
}

bool	check_philo_died(t_table *table, long id)
{
	bool	is_died;
	long	timestamp;

	ft_pthread_mutex_lock(&table->eat_time_mutex[id]);
	timestamp = get_timestamp();
	if (table->philos[id]->prev_eat_time == 0 
		&& timestamp - table->start_time >= table->rule->die
		|| table->philos[id]->prev_eat_time > 0
		&& timestamp - table->philos[id]->prev_eat_time >= table->rule->die)
	{
		set_finish(table);
		is_died = true;
		printf("%ld\t%ld died\n", get_timestamp() - table->start_time, id + 1);
	}
	ft_pthread_mutex_unlock(&table->eat_time_mutex[id]);
	return (is_died);
}

void	*monitor_routine(void *arg)
{
	t_table	*table;
	long	i;
	bool	eat_ok;

	table = (t_table *)arg;
	while (true)
	{
		i = 0;
		eat_ok = true;
		while (i < table->rule->philo_num)
		{
			if (table->rule->eat_count < 0
				|| get_eat_count_of_philo(table, i) < table->rule->eat_count)
				eat_ok = false;
			if (check_philo_died(table, i))
				return (NULL);
			i++;
		}
		if (eat_ok)
		{
			set_finish(table);
			return (NULL);
		}
	}
	return (NULL);
}
