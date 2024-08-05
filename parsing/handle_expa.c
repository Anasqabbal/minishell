/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:31:51 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/05 13:20:23 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	exig(char *str, int x)
{
	int	len;
	int	count;

	len = x - 1;
	count = 0;
	while (len > 0 && (str[len] == '"'
			|| ft_isalnum(str[len]) || ft_isspecial(str[len])))
	{
		if (str[len] == '"')
			count++;
		len--;
	}
	if (len - 1 >= 0 && ((str[len - 1] == '>' || str[len - 1] == '<')
			&& (count == 0 || count % 2 == 0)))
		return (0);
	return (1);
}

void	expans_but_nul_1(char *cmd, char *str, t_ndx *ind)
{
	int	l;

	l = 0;
	if (!exig(str, ind->x))
	{
		while (str[ind->x] && l < ind->var_len + 1)
		{
			cmd[ind->y++] = str[ind->x++];
			l++;
		}
	}
}

void	expans_but_non_nul(char *cmd, char *str, t_ndx *ind)
{
	int	x;

	x = 0;
	while (str[ind->x] && x < ind->var_len + 1)
	{
		cmd[ind->y++] = str[ind->x++];
		x++;
	}
}

void	its_not_a_var(char *str, char *cmd, t_ndx *ind)
{
	int	z;

	z = 0;
	if (ind->x - 2 >= 0 && (str[ind->x - 2] == '>' || str[ind->x - 2] == '<'))
	{
		while (z < ind->var_len + 1)
		{
			cmd[ind->y++] = str[ind->x++];
			z++;
		}
	}
	else
		ind->x += ind->var_len + 1;
}

void	handle_expa_suc(char *expans, char *cmd, t_ndx *ind, char *str)
{
	int	blink;

	blink = 0;
	turn_expans(expans);
	if ((eqaulsign(str, ind) || w_s(expans))
		&& count_exp_qts(str, ind))
	{
		ft_strcpy(&cmd[ind->y], "\"");
		ind->y += 1;
		blink = 1;
	}
	ft_strcpy(&cmd[ind->y], expans);
	if (blink == 1)
	{
		ind->y += ft_strlen(expans);
		ft_strcpy(&cmd[ind->y], "\"");
		ind->y += 1;
	}
	else
		ind->y += ft_strlen(expans);
	ind->x += ind->var_len + 1;
}
