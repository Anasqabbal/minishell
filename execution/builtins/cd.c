/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:06:21 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/21 13:09:48 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	cd_relative_path(char *str, t_list **env)
{
	char	*old_pwd;
	int		len;
	char	l[PATH_MAX];

	if (str[0] == '-' && ft_strlen(str) == 1)
		return (to_old_one(env, getcwd(l, sizeof(l))));
	if (!getcwd(l, sizeof(l)))
		return (perror("cd :"), 1);
	if (chdir(str))
		return (perror("chdir"), 1);
	len = ft_strlen(l);
	old_pwd = ft_calloc(sizeof(char), len);
	if (!old_pwd)
		return (1);
	ft_memcpy(old_pwd, l, len);
	if (join_and_export("OLDPWD=", old_pwd, env, "PWD="))
		return (free(old_pwd), 1);
	return (free(old_pwd), 0);
	return (0);
}

int	cd_absolute_path(char *str, t_list **env)
{
	char	old[PATH_MAX];

	if (!getcwd(old, sizeof(old)))
		return (perror("cd"), 1);
	if (chdir(str))
		return (perror("chdir"), 1);
	if (join_and_export("OLDPWD=", old, env, "PWD="))
		return (1);
	return (0);
}

char	*move_back1(char *str, char *res, int *i, t_list **env)
{
	static char	sp[PATH_MAX];
	char		*new_path;
	char		*tmp;
	char		o[PATH_MAX];

	getcwd(o, sizeof(o));
	if (!res && !((*i)++))
		return (ft_strcpy(sp, o), ft_putstr_fd("cd :", 2), perror(str), NULL);
	else if (!res && i)
	{
		ft_putstr_fd("cd: error retrieving current directory", 2);
		ft_putstr_fd(": getcwd: cannot access parent directories", 2);
		ft_putendl_fd(": No such file or directory", 2);
		chdir(str);
		join_and_export("OLDPWD=", sp, env, "PWD=");
		tmp = ft_strjoin(sp, "/");
		if (!tmp)
			return (NULL);
		new_path = my_strjoin(tmp, str);
		if (!new_path)
			return (NULL);
		ft_strcpy(sp, new_path);
		join_and_export("PWD=", new_path, env, "PWD=");
	}
	return (sp);
}

int	move_back(char	*str, t_list	**env)
{
	char		o[PATH_MAX];
	char		n[PATH_MAX];
	char static	*sp;
	static int	i;
	char		*res;

	res = getcwd(o, sizeof(o));
	if (!ft_check_dir(str))
		chdir(str);
	if (!getcwd(n, sizeof(n)))
	{
		sp = move_back1(str, res, &i, env);
		if (sp)
			return (0);
		else
			return (1);
	}
	if (!i)
		join_and_export("OLDPWD=", o, env, "PWD=");
	else
		join_and_export("OLDPWD=", sp, env, "PWD=");
	join_and_export("PWD=", n, env, "PWD=");
	return (i = 0, 0);
}

int	ft_cd(char **str, t_list **env, char *path)
{
	char	s[PATH_MAX];

	(void)path;
	if (it_is_with_options(str, 0, "cd"))
		return (1);
	if (!str[0] || !ft_strncmp(str[0], "~", ft_strlen(str[0]))
		|| (!ft_strncmp(str[0], "--", 2) && ft_strlen(str[0]) == 2))
		return (to_home(*env));
	if (check_dir_access(str))
		return (1);
	if (str[0][0] == '/')
		cd_absolute_path(str[0], env);
	else
	{
		if (ft_strnstr("..", str[0]
				, ft_strlen(str[0])) && ft_strlen(str[0]) % 2 == 0)
			return (move_back(str[0], env));
		cd_relative_path(str[0], env);
		getcwd(s, sizeof(s));
		if (join_and_export("PWD=", s, env, "PWD="))
			return (1);
	}
	return (0);
}
