/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_6.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 13:23:34 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/07 20:33:09 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_expa_handel(char *cmd, char *str, t_list *env)
{
	ft_lstclear(&env, free);
	free(cmd);
	free(str);
	exit(1);
}

int	spac(char *expans, char *str, char *cmd, t_list *env)
{
	char	**hold;
	int		count;

	count = 0;
	hold = pro_split(expans);
	if (!hold)
	{
		ft_lstclear(&env, free);
		free(cmd);
		free(str);
		free(expans);
		exit(1);
	}
	count = arg_count(hold);
	free_it(hold, count);
	return (count);
}

void	expans_but_nul_2(char *cmd, t_ndx *ind, char *expans)
{
	ft_strcpy(&cmd[ind->y], expans);
	ind->y += ft_strlen(expans);
	ind->x += ind->var_len + 1;
}

int	handle_loop_ndx(char *str, int *hold)
{
	int	count;

	count = 0;
	while (1)
	{
		if (str[*hold] == ' ' || !str[*hold])
		{
			turn_back(str, 1);
			break ;
		}
		if (str[*hold] * -1 == '$')
		{
			turn_back(str, 1);
			if (turn_dollar_2(str, *hold))
				count++;
			turn_back(str, 1);
		}
		if (str[*hold])
			(*hold)++;
	}
	return (count);
}

int	w_s(char *expans)
{
	int	x;

	x = 0;
	while (expans[x])
	{
		if (expans[x] != ' ' && !(expans[x] >= 9 && expans[x] <= 13))
			return (0);
		x++;
	}
	return (1);
}
