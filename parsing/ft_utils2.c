/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 20:38:13 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/22 16:36:44 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *expand_variable(char *str, t_list *env, int *ndx)
{
	char *hold;
	t_list *expa;   
	char *hold_h;
	int len;

	hold = ft_strjoin(str, "=");
	if(!hold)
		return(free(str), NULL);
	len = ft_strlen(hold);
	expa = ft_getenv(hold, env);
	if (!expa)
	{
		(*ndx) = 1;
		return (free(hold), NULL);
	}
	free(hold);	
	hold_h = ft_strdup(expa->content + len);
	return (hold_h);
}

char *extract_virable(char *str, int *var_len)
{
	int x;
	char *var;
	int y ;

	x = 0;
	x++;
	while (ft_isalnum(str[x]) || str[x] == '_')
		x++;
	var = (char *)malloc((x + 1) * sizeof(char));
	if (!var)
	{
		free(str);
		exit(1);
	}
	y = 0;
	while (y < x)
	{
		var[y] = str[y];
		y++;
	}
	var[y] = '\0';
	(*var_len) = x;
	return (var);
}

void turn_back_dollar(char *str)
{
	int x;

	x = 0;
	while (str[x])
	{
		if (str[x] * - 1 == '$')
			str[x] *= -1;
		x++;
	}
}
void the_turns(char *str, int ndx)
{
	if (ndx == 0)
	{
		turn_back(str, 1);
		turn_double(str, 1);
	}
	else if(ndx == 1)
	{
		turn_single(str, 1);
		turn_back_dollar(str);
		turn_single(str, 1);
	}
}

char *cmd_expa_h(char *str)
{
	turn_single(str, 1);
	turn_here_do(str);
	return (blurr_dollar(str));
}

