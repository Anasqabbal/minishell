/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 10:04:49 by anqabbal          #+#    #+#             */
/*   Updated: 2023/11/27 12:45:15 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	my_strcmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;
	size_t	k;

	i = 0;
	k = 0;
	while (*(s1 + i) && i < n)
	{
		if (*(s1 + i) == *(s2 + k) && i < n)
		{
			if (*(s2 + k + 1) == '\0')
				return (0);
			i++;
			k++;
		}
		else
			return (1);
	}
	return (1);
}

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	i;
	size_t	check;

	i = 0;
	if (*((char *) needle + i) == 0)
		return ((char *)haystack);
	while (i < len && *(haystack + i))
	{
		check = my_strcmp((haystack + i), (needle), len - i);
		if (check == 0)
			return ((char *)haystack + i);
		else
			i++;
	}
	return (NULL);
}
