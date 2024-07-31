/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 19:17:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/30 16:58:47 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	int		len;
	char	*arr;

	len = ft_strlen(s1);
	arr = malloc((len + 1) * (sizeof (char)));
	if (!arr)
		return (0);
	ft_memcpy(arr, s1, len);
	arr[len] = '\0';
	return (arr);
}
