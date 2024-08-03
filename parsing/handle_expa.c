/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_expa.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 21:31:51 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/03 14:30:16 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_ambig(char *str, int x)
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

void	expans_but_nul_1(char *cmd, char *str, t_ndx *ind, int var_len)
{
	int	l;

	l = 0;
	if (!export_ambig(str, ind->x))
	{
		while (str[ind->x] && l < var_len + 1)
		{
			cmd[ind->y++] = str[ind->x++];
			l++;
		}
	}
}

void	expans_but_non_nul(char *cmd, char *str, t_ndx *ind, int var_len)
{
	int	x;

	x = 0;
	while (str[ind->x] && x < var_len + 1)
	{
		cmd[ind->y++] = str[ind->x++];
		x++;
	}
}

void	its_not_a_var(char *str, char *cmd, t_ndx *ind, int var_len)
{
	int	z;

	z = 0;
	if (ind->x - 2 >= 0 && (str[ind->x - 2] == '>' || str[ind->x - 2] == '<'))
	{
		while (z < var_len + 1)
		{
			cmd[ind->y++] = str[ind->x++];
			z++;
		}
	}
	else
		ind->x += var_len + 1;
}

void	handle_expa_suc(char *expans, char *cmd, t_ndx *ind, int var_len)
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
	ft_strcpy(&cmd[ind->y], expans);
	ind->y += ft_strlen(expans);
	ind->x += var_len + 1;
}
