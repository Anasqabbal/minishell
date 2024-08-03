/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skkiping_dollars_h.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:17:58 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/31 21:04:49 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	small_while(char *str, char *cmd, t_ndx_c *indi, int count)
{
	int	z;

	z = 0;
	while (z < count)
	{
		if (str[indi->x] == '$')
			str[indi->x] *= -1;
		cmd[indi->y++] = str[indi->x++];
		z++;
	}
}

void	dollar_while_h4(char *str, char *cmd, t_ndx_c *indi, int count)
{
	if (count % 2 != 0)
	{
		indi->x++;
		small_while(str, cmd, indi, count);
	}
	else
		small_while(str, cmd, indi, count);
}

void	dollar_while_h5(char *str, char *cmd, t_ndx_c *indi, int count)
{
	int	z;

	z = 0;
	if (count % 2 != 0)
	{
		while (z < (count - 1))
		{
			if (str[indi->x] == '$')
				str[indi->x] *= -1;
			cmd[indi->y++] = str[indi->x++];
			z++;
		}
		cmd[indi->y++] = str[indi->x++];
	}
	else
		small_while(str, cmd, indi, count);
}

void	dollar_while_h3(char *str, char *cmd, t_ndx_c *indi)
{
	int	hold;
	int	count;

	hold = indi->x;
	count = 0;
	while (str[hold] == '$')
	{
		hold++;
		count++;
	}
	if ((str[hold] == '"' || str[hold] == '\'') && !turn_dollar(str, hold - 1))
		dollar_while_h4(str, cmd, indi, count);
	else
		dollar_while_h5(str, cmd, indi, count);
}

void	the_three_1(char *str, char *cmd, t_ndx_c *indi)
{
	cmd[indi->y++] = str[indi->x++];
	cmd[indi->y++] = str[indi->x++];
	cmd[indi->y++] = str[indi->x++];
}
