/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_nbr_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:47:55 by anqabbal          #+#    #+#             */
/*   Updated: 2024/02/27 12:06:11 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft__putnbr_fd(int n, int fd)
{
	unsigned int	nb;
	int				count;

	count = 0;
	if (fd < 0)
		return (-1);
	nb = n;
	if (n < 0)
	{
		count += ft__putchar_fd('-', fd);
		nb = n * -1;
	}
	if (nb > 9)
	{
		count += ft__putnbr_fd(nb / 10, fd);
		count += ft__putnbr_fd(nb % 10, fd);
	}
	if (nb >= 0 && nb <= 9)
		count += ft__putchar_fd((nb + 48), fd);
	return (count);
}
