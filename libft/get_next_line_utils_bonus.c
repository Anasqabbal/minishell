/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 15:18:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/03/08 15:54:02 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*my_calloc(size_t count, size_t size)
{
	void	*arr;
	size_t	i;

	if (((int)count < 0 && (int)size < 0))
		return (0);
	arr = malloc(size * count);
	if (!arr)
		return (NULL);
	i = 0;
	while (i < (count * size))
	{
		*((char *)arr + i) = '\0';
		i++;
	}
	return (arr);
}

char	*to_join(char *s1, char *s2, int indice)
{
	char	*str1;
	char	*str2;

	str1 = s1;
	str2 = s2;
	if (indice == 0)
	{
		free(s1);
		s1 = NULL;
		return (NULL);
	}
	s1 = my_strjoin(s1, s2);
	if (!s1)
		return (to_join(str1, NULL, 0));
	free(str1);
	str1 = NULL;
	if (indice == 1)
	{
		free (str2);
		str2 = NULL;
	}
	return (s1);
}

void	*my_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	if (!dst && !src)
		return (NULL);
	if (dst == src)
		return (dst);
	while (i < n)
	{
		*((char *) dst + i) = *((char *) src + i);
		i++;
	}
	return (dst);
}

char	*my_strjoin(char *s1, char *s2)
{
	ssize_t		len;
	ssize_t		len2;
	char		*arr;

	len = 0;
	len2 = 0;
	if ((!s1 && !s2))
		return (0);
	else if (!s1)
		return (my_strjoin("", s2));
	else if (!s2)
		return (my_strjoin(s1, ""));
	while (s1[len])
		len++;
	while (s2[len2])
		len2++;
	arr = malloc(sizeof(char) * len + len2 + 1);
	if (!arr)
		return (NULL);
	my_memcpy(arr, s1, len);
	my_memcpy(arr + len, s2, len2);
	*(arr + len + len2) = '\0';
	return (arr);
}

char	*my_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		if (*((char *)s + i) == (char)c)
			return ((char *)s + i);
		i++;
	}
	if (*((char *)s + i) == (char)c)
		return ((char *)s + i);
	return (NULL);
}
