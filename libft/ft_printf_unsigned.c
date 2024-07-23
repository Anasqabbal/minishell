/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_unsigned.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 21:36:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/25 19:58:54 by marvin           ###   ########.fr       */
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
	if ( nb <= 9)
		count += ft__putchar_fd((nb + 48), fd);
	return (count);
}
