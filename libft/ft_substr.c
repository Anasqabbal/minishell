/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:27:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/18 11:42:23 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*arr;

	if (!s)
		return (0);
	if (start >= ft_strlen(s) || len == 0)
	{
		arr = ft_calloc(1, sizeof(char));
		if (!arr)
			return (0);
		return (arr);
	}
	if (len > (ft_strlen(s) - start))
		len = ft_strlen(s) - start;
	arr = ft_calloc(len + 1, sizeof(char));
	if (!arr)
		return (0);
	ft_memcpy(arr, s + start, len);
	return (arr);
}
