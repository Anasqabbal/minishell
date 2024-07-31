/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:12:54 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/30 20:18:03 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_syntax_msg(char *str, int len)
{
	char	last;
	char	third_last;
	char	fourth_last;

	last = str[len - 1];
	if (len > 3)
		third_last = str[len - 3];
	if (len > 4)
		fourth_last = str[len - 4];
	if ((last == '<' || last == '>')
		&& (fourth_last != '<' && fourth_last != '>')
		&& (third_last != '<' && third_last != '>'))
		return (0);
	return (1);
}

static char	*ft_syntax_h3(char *str, int x)
{
	char	hold;

	while ((size_t)x < ft_strlen(str))
	{
		if (str[x] == '"' || str[x] == '\'')
		{
			hold = str[x];
			x++;
			if (str[x] == '\0')
				break ;
			while ((size_t)x < ft_strlen(str))
			{
				if (str[x] == hold)
					break ;
				str[x++] *= -1;
			}
		}
		if (!ft_syntax_h2(str, x))
			return (NULL);
		x++;
	}
	return (str);
}

static int	ft_syntax_h(char *str, int *x)
{
	int	len;

	turn_back(str, 1);
	replacewihte_s(str);
	turn_back(str, 1);
	len = ft_strlen(str);
	while (str[(*x)] == ' ' || (str[(*x)] > 9 && str[(*x)] < 13))
		(*x)++;
	if (str[*x] == '|' && str[*x + 1] != '|')
	{
		error_msg(str[*x]);
		return (0);
	}
	while ((str[len - 1] == ' ' || (str[len - 1] >= 9
				&& str[len - 1] <= 13)) && len > 1)
		len--;
	if (!ft_syntax_msg(str, len))
	{
		error_msg(str[len - 1]);
		return (0);
	}
	return (len);
}

static int	ft_syntax(char *stl)
{
	int	x;
	int	len;

	x = 0;
	len = ft_syntax_h(stl, &x);
	if (!len)
		return (0);
	if (!ft_syntax_h3(stl, x))
		return (0);
	if ((stl[len - 1] == '|' && stl[len - 2] != '|'))
	{
		error_msg(stl[len - 1]);
		return (0);
	}
	return (1);
}

int	check_syntax(char *input, t_list *env, t_prs **node, int *ret)
{
	char	*raw;
	int		opp;
	int		qts;

	opp = 0;
	qts = 0;
	if (input[0] == '\0')
		return (1);
	raw = ft_strdup(input);
	if (!raw)
		return (-1);
	if (!ft_syntax(raw))
		return (free(raw), *ret = 258, 0);
	if (!check_qts(raw, &opp, &qts))
		return (free(raw), *ret = 258, 0);
	(*node) = pipe_split(raw, opp, env, ret);
	return (1);
}
