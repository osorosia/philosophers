/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_mutex_lock.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:29:31 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:25:32 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_pthread_mutex_lock(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_lock(mutex);
	if (ret != 0)
		printf("pthread_mutex_lock: error\n");
	return (ret);
}
