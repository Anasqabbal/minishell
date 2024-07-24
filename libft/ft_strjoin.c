/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:55:31 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/08 17:18:02 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		len;
	int		len2;
	char	*arr;

	if ((!s1 || !s2))
		return (0);
	len = ft_strlen(s1);
	len2 = ft_strlen(s2);
	arr = malloc(sizeof(char) * len + len2 + 1);
	if (!arr)
		return (0);
	ft_memmove(arr, s1, len);
	ft_memmove(arr + len, s2, len2);
	*(arr + len + len2) = '\0';
	return (arr);
}
