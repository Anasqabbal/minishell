/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:43:32 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/20 16:55:36 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *cmd_alloctation(char *str, t_list *env)
{
	char *cmd;

	cmd = (char *)malloc((calaculate_expan_len(str, env) + 1) * sizeof(char));
	if (!cmd)
	{
		free(str);
		exit(1);
	}
	return (cmd);
}
static char *extra_expa_var(char *str, t_list *env, int *var_len, int *ndx)
{
	char 	*var;
	char	*expans;

	var = extract_virable(str, var_len);
	expans = expand_variable(var, env, ndx);
	free(var);
	return(expans);
}
static void handle_expa_suc(char *expans, char *cmd, t_ndx *ind, int var_len)
{	
	ft_strcpy(&cmd[ind->y], expans);
	ind->y += ft_strlen(expans);
	ind->x += var_len + 1;
	free(expans);
}
static void handle_var_exp(char *str, t_list *env, char *cmd, t_ndx *ind)
{
	int 	var_len;
	int 	ndx;
	char	*expans;

	var_len = 0;
	ndx = 0;
	expans = extra_expa_var(&str[ind->x], env, &var_len, &ndx);
	if (expans)
		handle_expa_suc(expans, cmd, ind, var_len);
	else if(!expans && ndx == 0)
	{
		free(cmd);
		free(str);
		exit(1);
	}
	else if ((size_t)ind->x < ft_strlen(str))
		ind->x += var_len + 1;
}
int count_ex(char *cmd)
{
	int x;
	int count;

	count = 0;
	x = 0;
	while (cmd[x])
	{
		if (cmd[x] == '$' && cmd[x + 1] == '?')
			count++;
		x++;
	}
	return (count);
}
char *expand_ex_code(char *cmd, int *red)
{
	int x;
	int y;
	char *ex_code;
	char *str;
	int len;
	int count;

	ex_code = ft_itoa((*red));
	count = count_ex(cmd);
	len = ft_strlen(cmd) - (count * 2) + (ft_strlen(ex_code) * count);
	str = (char *)malloc((len + 1) * sizeof(char));
	if (!str)
	{
		free(ex_code);
		free(cmd);
		exit(1);
	}
	x = 0;
	y = 0;
	while (cmd[x])
	{
		if (cmd[x] == '$' && cmd[x + 1] == '?')
		{
			ft_strcpy(&str[y], ex_code);
			y += ft_strlen(ex_code);
			x += 2;  
		}
		else
			str[y++] = cmd[x++];
	}
	str[y] = '\0';
	return(free(ex_code), free(cmd), str);
}
char *cmd_expa(char *str, t_list *env, int *ret)
{
	char	*cmd;
	t_ndx	xy = {0, 0}; 
	
	cmd = cmd_alloctation(str, env);
	str = cmd_expa_h(str);
	turn_single(str, 1);
	while ((size_t)xy.x < ft_strlen(str))
	{
		if(str[xy.x] == '$')
		{
			if ((!ft_isalnum(str[xy.x + 1]) && str[xy.y + 1] != '_'))
			{
				cmd[xy.y++] = str[xy.x++];
				continue;
			}
			handle_var_exp(str, env, cmd, &xy);
		}
		else if ((size_t)xy.x < ft_strlen(str))
			cmd[xy.y++] = str[xy.x++];
	}
	cmd[xy.y] = '\0';
	the_turns(cmd, 1);
	cmd = expand_ex_code(cmd, ret);
	return(free(str), cmd);
}
