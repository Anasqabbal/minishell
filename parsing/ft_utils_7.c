/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_7.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 17:07:08 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/07 20:42:43 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	eqaulsign(char *str, t_ndx *ind)
{
	int	hold;

	hold = ind->x - 1;
	if (ind->x - 1 >= 0 && str[ind->x - 1] == '=')
		return (1);
	else if (ind->x - 1 >= 0 && str[ind->x - 1] == '"')
	{
		while (hold >= 0 && str[hold] == '"')
			hold--;
		if (str[hold] == '=')
			return (1);
	}
	return (0);
}

void	turn_expans(char *expans)
{
	int	x;

	x = 0;
	while (expans[x])
	{
		if (expans[x] == '"' || expans[x] == '\''
			|| expans[x] == '$' || expans[x] == '|')
			expans[x] *= -1;
		x++;
	}
}

void	retunr_ndx_cop(char *str, char *cmd, int *y, int *x)
{
	cmd[(*y)++] = str[(*x)++];
	cmd[(*y)++] = '(';
}

int	turn_dollar_here(char *str, int y)
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
					if ((str[y] == '<' || str[y] == '>') && y > ho && y < x)
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
