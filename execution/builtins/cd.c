/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:06:21 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/05 10:00:16 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	*complete_move_back1(char *str, char **tmp,
	char sp[][PATH_MAX], t_list **env)
{
	ft_putstr_fd("cd: error retrieving current directory", 2);
	ft_putstr_fd(": getcwd: cannot access parent directories", 2);
	ft_putendl_fd(": No such file or directory", 2);
	chdir(str);
	if (join_and_export("OLDPWD=", (*sp), env, "PWD=") == -1)
		return (NULL);
	(*tmp) = ft_strjoin((*sp), "/");
	if (!(*tmp))
		return (NULL);
	return (*tmp);
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
	else if (!res)
	{
		if (!complete_move_back1(str, &tmp, &sp, env))
			return (NULL);
		new_path = my_strjoin(tmp, str);
		if (!new_path)
			return (free(tmp), NULL);
		ft_strcpy(sp, new_path);
		if (join_and_export("PWD=", new_path, env, "PWD=") == -1)
			return (NULL);
		free(tmp);
		free(new_path);
	}
	return (sp);
}

static int	check_move_back(char *o, char *sp, t_list **env, int i)
{
	if (!i)
	{
		if (join_and_export("OLDPWD=", o, env, "PWD=") == -1)
			return (-1);
	}
	else
	{
		if (join_and_export("OLDPWD=", sp, env, "PWD=") == -1)
			return (-1);
	}
	return (0);
}

int	move_back(char	*str, t_list	**env)
{
	char		o[PATH_MAX];
	char		n[PATH_MAX];
	static char	*sp;
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
	if (check_move_back(o, sp, env, i) == -1)
		return (-1);
	if (join_and_export("PWD=", n, env, "PWD=") == -1)
		return (-1);
	return (i = 0, 0);
}

int	ft_cd(char **str, t_list **env, int ret)
{
	if (str && str[0] && str[0][0] == '\0')
		return (0);
	if (it_is_with_options(str, 0, "cd"))
		return (2);
	if (!str[0] || !ft_strncmp(str[0], "~", ft_strlen(str[0]))
		|| (!ft_strncmp(str[0], "--", 2) && ft_strlen(str[0]) == 2))
		return (to_home(env));
	ret = check_dir_access(str);
	if (ret == -1)
		return (-1);
	else if (ret)
		return (ret);
	return (ft_do_cd(str, env));
}
