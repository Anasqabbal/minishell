/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:41:45 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/08 14:25:39 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	cd_print_error(char *s1, char *s2)
{
	ft_putstr_fd("cd : ", 2);
	ft_putstr_fd(s1, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(s2, 2);
}

int	initialize_sing(t_prs **lst, t_list **env, t_exec *e, t_sing *s)
{
	s->save = dup(STDOUT_FILENO);
	if (s->save < 0)
		return (perror("dup"), -1);
	s->out = -1;
	s->in = -1;
	s->ret = 0;
	s->envp = env;
	s->lst = *lst;
	s->e = e;
	return (0);
}

int	ft_export_(t_list **env, char **str, t_exec *e)
{
	char	*res1;
	int		i;

	i = 0;
	while (str && str[i + 1])
		i++;
	if (str)
	{
		if ((!ft_strncmp(str[i], "$?", 2)) && ft_strlen(str[i]) == 2)
			return (export_exit_code(env, e));
		if (ft_strchr(str[i], '='))
			return (export_with_equal(str[i], env));
		res1 = my_strjoin("_=", str[i]);
	}
	else
		res1 = my_strjoin("_=", NULL);
	if (!res1)
		return (-1);
	if (!export1(res1, env))
		return (free(res1), -1);
	return (free(res1), 0);
}

int	ft_do_cd(char **str, t_list **env)
{
	char	s[PATH_MAX];

	if (str[0][0] == '/')
		cd_absolute_path(str[0], env);
	else
	{
		if (ft_strnstr("..", str[0]
				, ft_strlen(str[0])) && ft_strlen(str[0]) % 2 == 0)
			return (move_back(str[0], env));
		cd_relative_path(str[0], env);
		getcwd(s, sizeof(s));
		if (join_and_export("PWD=", s, env, "PWD=") == -1)
			return (-1);
	}
	return (0);
}
