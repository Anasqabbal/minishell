/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 16:52:39 by anqabbal          #+#    #+#             */
/*   Updated: 2023/12/07 16:52:39 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**split_free(char **strings, int j)
{
	while (j > 0)
	{
		free(strings[--j]);
	}
	free(strings);
	strings = NULL;
	return (strings);
}

int	split_strlen(const char *s, char c, int indice)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (*(s + i) == c && *(s + i))
		i++;
	while (*(s + i) && indice == 0)
	{
		if ((*(s + i) != c && *(s + i + 1) == c))
			count++;
		else if ((*(s + i) != c && *(s + i + 1) == '\0'))
			count++;
		i++;
	}
	while (*(s + i) && indice != 0)
	{
		if ((*(s + i++) != c))
			count++;
		if (*(s + i) == c)
			break ;
	}
	return (count);
}

static char	**cal_alloc_set(const char *s, char c, char **strings, int s_len)
{
	int		len;
	int		i;
	int		j;
	int		res;

	i = 0;
	j = 0;
	len = split_strlen(s, c, 0);
	while (i < s_len)
	{
		while (*(s + i) == c && i < s_len)
			i++;
		res = split_strlen(s + i, c, 1);
		if (res != 0 && j < len)
		{
			strings[j] = ft_calloc(res + 1, sizeof(char));
			if (!(strings[j]))
				return (split_free(strings, j));
		}
		if (res != 0 && strings && j < len && i < s_len)
			ft_memmove(strings[j++], s + i, res);
		i += res;
	}
	return (strings);
}

char	**ft_split(const char *s, char c)
{
	int		res;
	char	**strings;
	int		s_len;

	if (!s)
		return (0);
	res = split_strlen(s, c, 0);
	s_len = ft_strlen(s);
	if (res == 0)
	{
		strings = ft_calloc(1, sizeof(char *));
		if (!strings)
			return (0);
	}
	else
	{
		strings = ft_calloc(res + 1, sizeof(char *));
		if (!strings)
			return (0);
		strings = cal_alloc_set(s, c, strings, s_len);
	}
	return (strings);
}
