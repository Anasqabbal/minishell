/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf_str_fd.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 10:45:16 by anqabbal          #+#    #+#             */
/*   Updated: 2024/02/27 12:05:02 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft__putstr_fd(char *s, int fd)
{
	int	i;

	i = 0;
	if (fd < 0)
		return (-1);
	else if (!s)
	{
		ft_putstr_fd("(null)", 1);
		return (6);
	}
	while (*(s + i))
	{
		ft_putchar_fd(*(s + i), fd);
		i++;
	}
	return (i);
}
