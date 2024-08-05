/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 19:47:53 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/05 12:44:29 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	expo_turn(char **str)
{
	int	x;
	int	y;

	y = 0;
	while (str[y])
	{
		x = 0;
		while (str[y][x])
		{
			if (str[y][x] < 0)
				str[y][x] *= -1;
			x++;
		}
		y++;
	}
}

void	turning_it_back(t_prs *head)
{
	t_prs	*curr;
	int		x;

	curr = head;
	while (curr != NULL)
	{
		x = 0;
		if (curr->cmd)
		{
			while (curr->cmd[x])
			{
				if (curr->cmd[x] < 0)
					curr->cmd[x] *= -1;
				x++;
			}
		}
		if (curr->arg)
			expo_turn(curr->arg);
		if (curr->red)
			expo_turn(curr->red);
		if (curr->opts)
			expo_turn(curr->opts);
		curr = curr->next;
	}
}

void	free_env(char *str, t_list *env)
{
	if (!str)
	{
		ft_lstclear(&env, free);
		exit(1);
	}
}

void	the_three(char *str, char *cmd, int *y, int *x)
{
	cmd[(*y)++] = str[(*x)++];
	cmd[(*y)++] = str[(*x)++];
	cmd[(*y)++] = str[(*x)++];
}

int	turn_dollar_2(char *str, int y)
{
	int		x;
	char	hold;
	int		ho;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '\'')
		{
			hold = str[x];
			ho = x;
			while (str[++x] != '\0')
			{
				if (str[x] == hold)
				{
					if (str[y] == '$' && y > ho && y < x)
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
