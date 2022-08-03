/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:51:45 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 13:54:11 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_rule(t_table *table, int argc, char **argv)
{
	t_rule	*rule;

	rule = malloc(sizeof(t_rule));
	if (rule == NULL)
		return (false);
	rule->philo_num = ft_atol(argv[1]);
	rule->die = ft_atol(argv[2]);
	rule->eat = ft_atol(argv[3]);
	rule->sleep = ft_atol(argv[4]);
	rule->eat_count = -1;
	if (argc == 6)
		rule->eat_count = ft_atol(argv[5]);
	table->rule = rule;
	return (true);
}

bool	set_forks(t_table *table)
{
	pthread_mutex_t	*forks;
	long			i;

	forks = ft_calloc(table->rule->philo_num, sizeof(pthread_mutex_t));
	if (forks == NULL)
		return (false);
	table->forks = forks;
	i = 0;
	while (i < table->rule->philo_num)
	{
		pthread_mutex_init(&forks[i], NULL);
		i++;
	}
	return (true);
}

bool	set_philos(t_table *table)
{
	t_philo	**philos;
	long	i;

	philos = ft_calloc(table->rule->philo_num, sizeof(t_philo *));
	if (philos == NULL)
		return (false);
	table->philos = philos;
	i = 0;
	while (i < table->rule->philo_num)
	{
		philos[i] = ft_calloc(1, sizeof(t_philo));
		if (philos[i] == NULL)
			return (false);
		philos[i]->id = i;
		philos[i]->table = table;
		philos[i]->rule = table->rule;
		i++;
	}
	return (true);
}

bool	set_mutex(t_table *table)
{
	pthread_mutex_t	*eat_count_mutex;
	pthread_mutex_t	*eat_time_mutex;
	long			i;

	eat_count_mutex = ft_calloc(
			table->rule->philo_num, sizeof(pthread_mutex_t));
	if (eat_count_mutex == NULL)
		return (false);
	table->eat_count_mutex = eat_count_mutex;
	eat_time_mutex = ft_calloc(table->rule->philo_num, sizeof(pthread_mutex_t));
	if (eat_time_mutex == NULL)
		return (false);
	table->eat_time_mutex = eat_time_mutex;
	i = 0;
	while (i < table->rule->philo_num)
	{
		pthread_mutex_init(&eat_count_mutex[i], NULL);
		pthread_mutex_init(&eat_time_mutex[i], NULL);
		i++;
	}
	pthread_mutex_init(&table->print_mutex, NULL);
	return (true);
}
