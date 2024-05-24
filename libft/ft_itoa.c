/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/04 09:43:28 by anqabbal          #+#    #+#             */
/*   Updated: 2023/12/05 09:55:53 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen1(int n)
{
	int				i;
	unsigned int	nb;

	i = 0;
	nb = n;
	if (n < 0)
	{
		nb = n * (-1);
		i++;
	}
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

static void	remainder_work(char *arr, int n, int i)
{
	int				s_l;
	unsigned int	nb;

	nb = n;
	s_l = my_strlen1(n) - 1;
	if (n < 0)
	{
		arr[i++] = '-';
		nb = n * -1;
	}
	while (nb > 0)
	{
		arr[s_l] = (nb % 10) + 48;
		nb /= 10;
		i++;
		s_l--;
	}
}

char	*ft_itoa(int n)
{
	int				len_of_n;
	char			*arr;
	int				i;

	i = 0;
	len_of_n = my_strlen1(n);
	if (n != 0)
	{
		arr = ft_calloc(sizeof(char), len_of_n + 1);
		if (!arr)
			return (0);
		if (n != 0)
			arr[len_of_n] = '\0';
		remainder_work(arr, n, i);
	}
	else
	{
		arr = ft_calloc(2, 1);
		if (!arr)
			return (0);
		arr[0] = '0';
	}
	return (arr);
}
