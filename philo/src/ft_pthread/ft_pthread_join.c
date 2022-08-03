/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pthread_join.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:27:07 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:24:02 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	ft_pthread_join(pthread_t th, void **value_ptr)
{
	int	ret;

	ret = pthread_join(th, value_ptr);
	if (ret != 0)
		printf("pthread_join: error\n");
	return (ret);
}
