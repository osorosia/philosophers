/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:54:17 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 18:22:03 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

bool	set_rule(t_table *table, int argc, char **argv);
bool	set_forks(t_table *table);
bool	set_philos(t_table *table);
bool	set_mutex(t_table *table);

t_table	*table_new(int argc, char **argv)
{
	t_table	*table;

	table = ft_calloc(1, sizeof(t_table));
	if (table == NULL)
		return (NULL);
	if (!set_rule(table, argc, argv)
		|| !set_philos(table)
		|| !set_forks(table)
		|| !set_mutex(table))
	{
		table_free(table);
		return (NULL);
	}
	return (table);
}

void	table_free(t_table *table)
{
	long	i;

	if (table == NULL)
		return ;
	i = 0;
	while (table->rule && i < table->rule->philo_num)
	{
		if (table->philos)
			free(table->philos[i]);
		if (table->forks)
			ft_pthread_mutex_destroy(&table->forks[i]);
		if (table->eat_count_mutex)
			ft_pthread_mutex_destroy(&table->eat_count_mutex[i]);
		if (table->eat_time_mutex)
			ft_pthread_mutex_destroy(&table->eat_time_mutex[i]);
		i++;
	}
	ft_pthread_mutex_destroy(&table->print_mutex);
	free(table->forks);
	free(table->eat_count_mutex);
	free(table->eat_time_mutex);
	free(table->philos);
	free(table->rule);
	free(table);
}
