/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_num.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rnishimo <rnishimo@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 10:27:48 by rnishimo          #+#    #+#             */
/*   Updated: 2022/08/03 10:28:08 by rnishimo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

bool	is_num(char *str)
{
	long	num;
	long	i;

	num = 0;
	i = 0;
	while (ft_isdigit(str[i]))
	{
		num = num * 10 + str[i] - '0';
		if (num > INT_MAX)
			return (false);
		i++;
	}
	return (i > 0 && str[i] == '\0');
}
