/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 13:56:15 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 13:59:51 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	usage(void)
{
	printf("\nusage:\n");
	printf("  ./philo\n");
	printf("    [number_of_philosophers]\n");
	printf("    [time_to_die]\n");
	printf("    [time_to_eat]\n");
	printf("    [time_to_sleep]\n");
	printf("    ([number_of_times_each_philosopher_must_eat])\n");
	printf("    \n");
	return (1);
}

bool	check_arg(int argc, char **argv)
{
	return ((argc == 5 || argc == 6)
		&& is_num(argv[1])
		&& is_num(argv[2])
		&& is_num(argv[3])
		&& is_num(argv[4])
		&& (argc != 6 || is_num(argv[5])));
}

int	start_dining_group_of_philos(
	t_table *table, pthread_t *philo_th, t_group group)
{
	long	i;
	int		ret;

	i = group;
	while (i < table->rule->philo_num)
	{
		ret = ft_pthread_create(
				&philo_th[i], NULL, philo_routine, table->philos[i]);
		if (ret != 0)
			return (1);
		i += 2;
	}
	return (0);
}

int	dining_philos(t_table *table)
{
	pthread_t	*philo_th;
	pthread_t	monitor_th;
	long		i;
	int			ret;

	philo_th = malloc(sizeof(pthread_t) * table->rule->philo_num);
	table->start_time = get_timestamp();
	start_dining_group_of_philos(table, philo_th, ODD);
	start_dining_group_of_philos(table, philo_th, EVEN);
	ret = ft_pthread_create(&monitor_th, NULL, monitor_routine, table);
	if (ret != 0)
		return (1);
	ft_pthread_join(monitor_th, NULL);
	i = 0;
	while (i < table->rule->philo_num)
	{
		ft_pthread_join(philo_th[i], NULL);
		i++;
	}
	free(philo_th);
	return (0);
}

int	main(int argc, char **argv)
{
	t_table	*table;
	int		ret;

	if (!check_arg(argc, argv))
		return (usage());
	table = table_new(argc, argv);
	if (table == NULL)
		return (1);
	ret = dining_philos(table);
	table_free(table);
	return (ret);
}
