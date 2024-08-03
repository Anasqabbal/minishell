/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:43:32 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/03 14:55:31 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char	*cmd_alloctation(char *str, t_list *env)
{
	char	*cmd;
	int		len;

	len = calaculate_expan_len(str, env) + count_expantion_here(str);
	cmd = (char *)malloc((len + 1) * sizeof(char));
	if (!cmd)
	{
		ft_lstclear(&env, free);
		free(str);
		exit(1);
	}
	the_turn_backs(str);
	return (cmd);
}

static char	*extra_expa_var(char *str, t_list *env, int *var_len, int *ndx)
{
	char	*var;
	char	*expans;

	var = extract_virable(str, var_len, env);
	expans = expand_variable(var, env, ndx);
	free(var);
	return (expans);
}

static void	handle_var_exp(char *str, t_list *env, char *cmd, t_ndx *ind)
{
	t_ndx_v	d;
	char	*expans;

	d.var_len = 0;
	d.ndx = 0;
	expans = extra_expa_var(&str[ind->x], env, &d.var_len, &d.ndx);
	if (expans && (expans[0] == '\0' || white_spaces(expans)))
	{
		if (!export_ambig(str, ind->x))
			expans_but_nul_1(cmd, str, ind, d.var_len);
		else
			expans_but_nul_2(cmd, ind, d.var_len, expans);
	}
	else if (expans && expans[0] != '\0' && !white_spaces(expans))
	{
		if (sp_a_c(expans, str, cmd, env) > 1 && !export_ambig(str, ind->x))
			expans_but_non_nul(cmd, str, ind, d.var_len);
		else
			handle_expa_suc(expans, cmd, ind, d.var_len);
	}
	else if (!expans && d.ndx == 0)
		free_expa_handel(cmd, str, env);
	else
		its_not_a_var(str, cmd, ind, d.var_len);
	free(expans);
}

char	*cmd_expa(char *str, t_list *env, int *red)
{
	char	*cmd;
	t_ndx	xy;

	xy = (t_ndx){0, 0};
	cmd = cmd_alloctation(str, env);
	while ((size_t)xy.x < ft_strlen(str))
	{
		if (str[xy.x] == '$')
		{
			if ((!ft_isalnum(str[xy.x + 1])) && str[xy.x + 1] != '_')
			{
				cmd[xy.y++] = str[xy.x++];
				continue ;
			}
			handle_var_exp(str, env, cmd, &xy);
		}
		else if ((size_t)xy.x < ft_strlen(str))
			expa_inside_here(str, cmd, &xy);
	}
	cmd[xy.y] = '\0';
	cmd = expand_ex_code(cmd, red, env, str);
	the_turns(cmd, 1);
	return (free(str), cmd);
}
