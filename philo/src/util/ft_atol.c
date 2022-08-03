/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 03:26:54 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:26:35 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

long	ft_atol(char *str)
{
	long	num;
	long	i;

	num = 0;
	i = 0;
	while (ft_isdigit(str[i]))
		num = num * 10 + str[i++] - '0';
	return (num);
}
