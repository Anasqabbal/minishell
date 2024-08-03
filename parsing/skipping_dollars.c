/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipping_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:43 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/03 15:10:47 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	dollar_while_h2(char *str, char *cmd, t_ndx_c *indi, int count)
{
	int	z;

	z = 0;
	if (count % 2 != 0)
	{
		indi->x++;
		while (z < count)
		{
			cmd[indi->y++] = str[indi->x++];
			z++;
		}
	}
	else
	{
		while (z < count)
		{
			cmd[indi->y++] = str[indi->x++];
			z++;
		}
	}
}

void	dollar_while_h1(char *str, char *cmd, t_ndx_c *indi)
{
	int	hold;
	int	count;

	hold = indi->x;
	count = 0;
	while (str[hold] == '$')
	{
		count++;
		hold++;
	}
	if ((str[hold] == '"' || str[hold] == '\'') && !turn_dollar(str, hold - 1))
		dollar_while_h2(str, cmd, indi, count);
	else
		cmd[indi->y++] = str[indi->x++];
}

void	dollar_while_h(char *str, char *cmd, t_ndx_c *indi)
{
	the_three_1(str, cmd, indi);
	turn_back(str, 1);
	while (str[indi->x])
	{
		if (str[indi->x] != ' ')
		{
			turn_back(str, 1);
			break ;
		}
		if (str[indi->x] == '$')
			dollar_while_h1(str, cmd, indi);
		else
			cmd[indi->y++] = str[indi->x++];
	}
}

void	dollar_while(char *str, char *cmd, t_ndx_c *indi, int ndx)
{
	while (str[indi->x])
	{
		if (str[indi->x] == '<' && str[indi->x + 1] == '<' && ndx == 1)
			dollar_while_h(str, cmd, indi);
		else if (str[indi->x] == '$')
			dollar_while_h3(str, cmd, indi);
		else
			cmd[indi->y++] = str[indi->x++];
	}
}

char	*dollar_sign(char *str, int ndx)
{
	char	*cmd;
	t_ndx_c	indi;

	indi = (t_ndx_c){0, 0};
	cmd = (char *)malloc((strlen(str) + 1) * sizeof(char));
	if (!cmd)
		return (free(cmd), NULL);
	dollar_while(str, cmd, &indi, ndx);
	cmd[indi.y] = '\0';
	return (free(str), cmd);
}
