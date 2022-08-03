#include "philo.h"

bool	print_action(t_philo *philo, t_action_kind act_kind)
{
	const char	*act[] = {
		"is eating", "is sleeping", "is thinking", "has taken a fork",
	};

	ft_pthread_mutex_lock(&philo->table->print_mutex);
	philo->prev_act_time = get_timestamp();
	if (philo->table->finish)
	{
		ft_pthread_mutex_unlock(&philo->table->print_mutex);
		return (false);
	}
	printf("%ld\t%ld %s\n", philo->prev_act_time - philo->table->start_time,
		   philo->id + 1, act[act_kind]);
	ft_pthread_mutex_unlock(&philo->table->print_mutex);
	return (true);
}
