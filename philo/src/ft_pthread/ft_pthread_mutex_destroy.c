/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_mutex_destroy.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:29:35 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:24:29 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	ft_pthread_mutex_destroy(pthread_mutex_t *mutex)
{
	int	ret;

	ret = pthread_mutex_destroy(mutex);
	if (ret != 0)
		printf("pthread_mutex_destroy: error\n");
}
