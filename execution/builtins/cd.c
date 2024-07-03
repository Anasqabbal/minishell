/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 17:06:21 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/29 14:47:16 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_getenv_ours1(char *str, t_list *env, char *path)
{
	char	*tmp;
	int		f_l;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return ;
	f_l = ft_strlen(str) - ft_strlen(tmp) + 1;
	while (env)
	{
		if (!ft_strncmp(env->content, str, f_l))
		{
			free(env->content);
			env->content = ft_strdup(path);
		}
		env = env->next;
	}
}
static t_list	*ft_getenva(char *str, t_list *env)
{
	char	*tmp;
	int		f_l;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (NULL);
	f_l = ft_strlen(str) - ft_strlen(tmp) + 1;
	while (env)
	{
		if (!ft_strncmp(env->content, str, f_l))
			return (env);
		env = env->next;
	}
	return (NULL);
}

int ft_cd(char **str , t_list *env, char *path)
{
	(void)path;
	static char lastdir[PATH_MAX];
	char *path_p;
	char *path_o;
	t_list *home;
	char *hm;
	int suc;
	struct stat file_stat;

	// if (str[1] != NULL && str[2] != NULL)
	// {
	// 	printf("cd: too many arguments\n");
	// 	return;
	// }
	// if (str[1] != NULL)
	// { 
	// 	printf("cd: string not in pwd: %s\n", str[1]);
	// 	return ;
	// }
	// if (str[0][0] == '\0')
	// 	return ;
	if (!str[0] || !ft_strncmp(str[0], "~", ft_strlen(str[0])) || !ft_strncmp(str[0], "--", ft_strlen(str[0])))
	{
		home = ft_getenva("HOME=", env);
		hm = ft_strdup(home->content);
		if (!hm)
			return (1);
		suc = chdir(hm + ft_strlen("HOME="));
		if (suc < 0)
			return (free(hm), 1);
		return (free(hm), 0);
	}
	else
	{
		if (lstat(str[0], &file_stat) == 0)
		{
			if (!S_ISDIR(file_stat.st_mode))
				return (printf("cd: %s: %s\n", strerror(20), str[0]), 1);
		}
		if (access(str[0], F_OK) == 0)
		{
			if (access(str[0], R_OK | W_OK) == -1)
				return (printf("cd: %s: %s\n", strerror(13), str[0]), 1);
		}
		else
			printf("cd: %s: %s\n", strerror(2), str[0]);
		getcwd(lastdir, sizeof(lastdir));
		printf("%s\n", lastdir);	
		if (!ft_strncmp(str[0], "/", ft_strlen(str[0])))
			suc = chdir("/");
		else if (!ft_strncmp(str[0], "-", ft_strlen(str[0])))
			suc = chdir(lastdir);
		else 
			suc = chdir(str[0]);
		if (suc == 0)
		{
			path_o = ft_strjoin("OLDPWD=", lastdir);
			ft_getenv_ours1("OLDPWD=", env, path_o);
			free(path_o);
		}
		
		getcwd(lastdir, sizeof(lastdir));	
		path_p = ft_strjoin("PWD=", lastdir);
		ft_getenv_ours1("PWD=", env, path_p);
		return (0);
	}
}