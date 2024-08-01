/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:48:57 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/01 11:41:01 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	put_error_msg(char *cmd, int ind)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(" :the subject requires this builtin without options", 2);
	if (ind == 1)
		ft_putstr_fd(" or arguments", 2);
	ft_putchar_fd('\n', 2);
	return (1);
}

int	check_echo_opts(char **opts)
{
	int	i;
	int	j;

	i = -1;
	while (opts[++i])
	{
		j = -1;
		while (opts[i][++j])
		{
			if (j == 0 && opts[i][j] == '-' && opts[i][j + 1])
			{
				if (opts[i][j + 1] == 'e' || opts[i][j + 1] == 'E')
					return (put_error_msg(opts[i], 0));
			}
			else if (j == 1 && opts[i][j - 1] == '-' && opts[i][j] == 'n'
				&& (opts[i][j + 1] == 'e' || opts[i][j + 1] == 'E'))
				return (put_error_msg(opts[i], 0));
		}
	}
	return (0);
}

int	it_is_with_options(char **opts, int ind1, char *cmd)
{
	int	i;

	i = 0;
	if (!opts[0])
		return (0);
	if (cmd && !ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		return (check_echo_opts(opts));
	if (cmd && !ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3 && ind1 == 1)
		return (put_error_msg(opts[0], 1));
	if (opts[0][i] == '-' && opts[0][i + 1])
	{
		if (cmd && !ft_strncmp("cd", cmd, 2)
			&& ft_strlen(cmd) == 2 && opts[0][i + 1] == '-')
			return (0);
		return (put_error_msg(opts[0], 0));
	}
	return (0);
}

int	ft_pwd(t_list *env, char **str)
{
	char	fpwd[PATH_MAX];

	(void)env;
	(void)str;
	if (it_is_with_options(str, 0, "pwd"))
		return (2);
	getcwd(fpwd, sizeof(fpwd));
	ft_printf("%s\n", fpwd);
	return (0);
}
