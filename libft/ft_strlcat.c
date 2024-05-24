/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/01 17:16:15 by anqabbal          #+#    #+#             */
/*   Updated: 2023/12/01 16:09:55 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dl;
	size_t	ii;
	size_t	sl;

	if (dstsize == 0 && !dst)
		return (my_strlen(src));
	dl = my_strlen(dst);
	sl = my_strlen(src);
	if (dstsize == 0)
		return (sl);
	if (dstsize <= dl)
		return (dstsize + sl);
	ii = 0;
	while (*src)
	{
		if (dl < dstsize - 1 && src[ii])
			dst[dl++] = src[ii++];
		else
			break ;
	}
	dst[dl] = '\0';
	return (((dl - ii) + sl));
}
