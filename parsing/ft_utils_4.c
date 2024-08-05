/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_4.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:27:31 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/05 13:00:20 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	cmd_expa_h1(char *str, t_ndx *ind)
{
	int	hold;
	int	grip;

	hold = ind->x;
	grip = 0;
	while (str[hold])
	{
		if (str[hold] == '<' && str[hold + 1] == '<'
			&& !turn_dollar_here(str, hold))
		{
			grip = hold;
			hold += 3;
			while (str[hold] && str[hold] != ' ')
			{
				if (str[hold] == '\'' || str[hold] == '"')
					return (grip);
				hold++;
			}
		}
		if (str[hold])
			hold++;
	}
	return (-1);
}

void	the_turn_backs(char *str)
{
	turn_back(str, 1);
	turn_here_do(str);
	turn_double(str, 1);
}

void	expa_inside_here(char *str, char *cmd, t_ndx *xy)
{
	if (xy->x == cmd_expa_h1(str, xy))
	{
		cmd[xy->y++] = str[xy->x++];
		cmd[xy->y++] = str[xy->x++];
		cmd[xy->y++] = '<';
	}
	else
		cmd[xy->y++] = str[xy->x++];
}

int	count_expantion_here(char *str)
{
	int	x;
	int	ndx;
	int	count;

	x = 0;
	ndx = 0;
	count = 0;
	while (str[x])
	{
		if (str[x] == '<' && str[x + 1] == '<')
		{
			x += 3;
			while (str[x] && str[x] != ' ')
			{
				if (str[x] == '\'' || str[x] == '"')
					ndx++;
				x++;
			}
			if (ndx != 0)
				count++;
		}
		if (str[x])
			x++;
	}
	return (count);
}

int	ft_isspecial(char c)
{
	if (!ft_isalnum(c) && !(c == ' ' || (c >= 9 && c <= 13)))
		return (1);
	return (0);
}
