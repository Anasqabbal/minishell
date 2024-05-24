/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_hexa.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 17:08:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/02/27 12:41:02 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	to_upper_case(int c)
{
	if (c >= 'a' && c <= 'z')
		return (c -= 32);
	else
		return (c);
}

int	ft__print_hexa(unsigned int nb, int indice)
{
	char	*arr;
	int		count;

	count = 0;
	arr = "0123456789abcdef";
	if (nb >= 16)
	{
		count += ft__print_hexa(nb / 16, indice);
		count += ft__print_hexa(nb % 16, indice);
	}
	if (nb < 16 && indice == 1)
		count += ft__putchar_fd(to_upper_case(arr[nb]), 1);
	else if (nb < 16 && indice == 0)
		count += ft__putchar_fd(arr[nb], 1);
	return (count);
}
