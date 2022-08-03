/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_create.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:27:03 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:25:15 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_pthread_create(pthread_t *th, const pthread_attr_t *attr,
					  void *(*start_routine)(void *), void *arg)
{
	int	ret;

	ret = pthread_create(th, attr, start_routine, arg);
	if (ret != 0)
		printf("pthread_create: error\n");
	return (ret);
}
