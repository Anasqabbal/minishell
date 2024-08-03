/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_5.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 17:16:48 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/03 14:22:30 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	turn_pipe(char *str, int y)
{
	int		x;
	char	hold;
	int		ho;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '"' || str[x] == '\'')
		{
			hold = str[x];
			ho = x;
			while (str[++x] != '\0')
			{
				if (str[x] == hold)
				{
					if (str[y] == '|' && y > ho && y < x)
						return (1);
					break ;
				}
			}
		}
		if (str[x])
			x++;
	}
	return (0);
}

int	ex_code_zero(char *str, int x)
{
	int	len;

	len = x - 1;
	while (len >= 0)
	{
		if (str[len] == '|' && !turn_pipe(str, len))
			return (1);
		len--;
	}
	return (0);
}

static int	count_args(char *str)
{
	int	x;
	int	word;

	x = 0;
	word = 0;
	while (str[x] != '\0')
	{
		while (str[x] != '\0' && (str[x] == ' '
				|| (str[x] >= 9 && str[x] <= 13)))
			x++;
		if (str[x] != '\0')
			word++;
		while (str[x] != '\0' && (str[x] != ' '
				&& !(str[x] >= 9 && str[x] <= 13)))
			x++;
	}
	return (word);
}

static char	*fillword(int *x, char *s)
{
	int		t;
	char	*str;
	int		y;
	int		wordsize;

	y = 0;
	while (s[*x] != '\0' && (s[*x] == ' '
			|| s[*x] == '\t' || s[*x] == '\n'))
		(*x)++;
	t = *x;
	while (s[*x] != '\0' && (s[*x] != ' '
			&& s[*x] != '\t' && s[*x] != '\n'))
		(*x)++;
	wordsize = *x - t;
	str = (char *)malloc((wordsize + 1) * sizeof(char));
	if (!str)
		return (0);
	while (t + y < *x)
	{
		str[y] = s[t + y];
		y++;
	}
	str[y] = '\0';
	return (str);
}

char	**pro_split(char *s)
{
	char	**str;
	int		y;
	int		x;
	int		i;

	y = 0;
	i = 0;
	x = 0;
	if (!s)
		return (0);
	str = (char **)malloc((count_args(s) + 1) * sizeof(char *));
	if (!str)
		return (0);
	while (y < count_args(s))
	{
		str[y] = fillword(&x, s);
		if (!str[y])
		{
			free_it(str, arg_count(str));
			return (NULL);
		}
		y++;
	}
	str[count_args(s)] = 0;
	return (str);
}
