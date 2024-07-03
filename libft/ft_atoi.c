/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 11:45:44 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/30 10:50:02 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	return_check(const char *str, long long res, int sign, int i)
{
	long long	old_res;

	old_res = res;
	while (str[i] >= 48 && str[i] <= 57)
	{
		if (res >= old_res)
		{
			old_res = res;
			res = res * 10 + (str[i++] - 48);
		}
		else
		{
			if (sign < 0)
				return (0);
			if (sign > 0)
				return (-1);
		}
	}
	return (res * sign);
}

int	ft_atoi(const char *str)
{
	int			i;
	int			sign;
	long long	res;

	sign = 1;
	i = 0;
	res = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			sign *= -1;
	}
	return (return_check(str, res, sign, i));
}
