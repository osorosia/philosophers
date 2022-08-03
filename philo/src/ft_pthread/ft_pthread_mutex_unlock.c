/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_mutex_unlock.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:29:29 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:25:45 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_pthread_mutex_unlock(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_unlock(mutex);
	if (ret != 0)
		printf("pthread_mutex_unlock: error\n");
	return (ret);
}
