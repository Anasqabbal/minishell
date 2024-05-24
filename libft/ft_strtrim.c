/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 14:57:27 by anqabbal          #+#    #+#             */
/*   Updated: 2023/12/02 14:57:28 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	cal_e(const char *s1, const char *set, int s_len)
{
	int	count;

	count = 0;
	while (s_len >= 0)
	{
		if (ft_memchr(set, *(s1 + s_len), ft_strlen(set)))
			count++;
		else
			return (count);
		s_len--;
	}
	return (count);
}

static int	cal_b(const char *s1, const char *set)
{
	int	j;
	int	count;

	j = 0;
	count = 0;
	while (*(s1 + j))
	{
		if (ft_memchr(set, *(s1 + j), ft_strlen(set)))
			count++;
		else
			return (count);
		j++;
	}
	return (count);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		b_len;
	int		e_len;
	int		s_len;
	char	*arr;
	int		f_len;

	if (!s1 || !set)
		return (0);
	s_len = ft_strlen(s1);
	b_len = cal_b(s1, set);
	e_len = cal_e(s1 + b_len, set, (s_len - b_len - 1));
	f_len = (s_len - (b_len + e_len));
	arr = malloc((f_len + 1) * sizeof(char));
	if (!arr)
		return (0);
	ft_memmove(arr, s1 + b_len, f_len);
	arr[f_len] = '\0';
	return (arr);
}
