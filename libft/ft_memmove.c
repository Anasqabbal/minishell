/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 14:04:48 by anqabbal          #+#    #+#             */
/*   Updated: 2023/12/01 09:33:48 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	if ((!dst && !src))
		return (0);
	if (len == 0)
		return (dst);
	if (dst < src || src == dst)
		ft_memcpy(dst, src, len);
	else
	{
		while (len > 0)
		{
			*((char *) dst + len - 1) = *((char *)src + len - 1);
			len--;
		}
	}
	return (dst);
}
