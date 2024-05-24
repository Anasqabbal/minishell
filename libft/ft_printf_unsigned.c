/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:36:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/02/27 12:43:38 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft__print_unsigned(unsigned int nb, int fd)
{
	int				count;

	count = 0;
	if (fd < 0)
		return (-1);
	if (nb > 9)
	{
		count += ft__print_unsigned(nb / 10, fd);
		count += ft__print_unsigned(nb % 10, fd);
	}
	if (nb >= 0 && nb <= 9)
		count += ft__putchar_fd((nb + 48), fd);
	return (count);
}
