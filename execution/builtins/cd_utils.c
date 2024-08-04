/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:50:05 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/04 10:27:50 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	join_slash_at_the_end(char **str, char **tmp)
{
	char	*res;
	char	*res1;

	if (!(*str))
		return (0);
	res = ft_strrchr(*str, '/');
	if (!res)
	{
		res = ft_strdup(*str);
		if (!res)
			return (-1);
		return (*tmp = res, 0);
	}
	else
	{
		res1 = ft_strjoin(*str, "/");
		if (!res1)
			return (-1);
		return (*tmp = res1, 0);
	}
}

int	check_dir_access(char **str)
{
	struct stat	file_stat;
	char		*tmp;

	tmp = NULL;
	if (str[0][0] == '-' && ft_strlen(str[0]) == 1)
		return (0);
	if (join_slash_at_the_end(str, &tmp) == -1)
		return (-1);
	if (lstat(tmp, &file_stat) == 0)
	{
		if (!S_ISDIR(file_stat.st_mode))
			return (free(tmp), printf("cd: %s: %s\n", strerror(20), str[0]), 1);
	}
	if (access(tmp, F_OK) == 0)
	{
		if (access(tmp, X_OK))
			return (free(tmp),
				printf("cd : %s: %s\n", str[0], strerror(13)), 1);
	}
	else
		return (free(tmp), printf("cd: %s: %s\n", str[0], strerror(2)), 1);
	return (free(tmp), 0);
}

int	to_home(t_list **env)
{
	t_list	*home;
	char	*hm;
	char	ol[PATH_MAX];
	char	cur[PATH_MAX];

	if (!ft_getenv_ours("HOME=", *env))
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	home = ft_getenv_ours("HOME=", *env);
	hm = home->content + ft_strlen("HOME");
	if (hm[0] == '\0')
		return (ft_putstr_fd("minishell: cd: HOME not set\n", 2), 1);
	if (hm[0] == '=' && hm[1] == '\0')
		return (0);
	hm = ft_strdup(home->content);
	if (!hm)
		return (1);
	getcwd(ol, sizeof(ol));
	if (chdir(hm + 5))
		return (perror("minishell: cd"), free(hm), 1);
	getcwd(cur, sizeof(cur));
	if (join_and_export("PWD=", cur, env, "PWD=") == -1
		|| join_and_export("OLDPWD=", ol, env, "PWD=") == -1)
		return (free(hm), -1);
	return (free(hm), 0);
}

int	to_old_one(t_list **env, char *lastdir)
{
	t_list	*old;
	char	*s;

	old = ft_getenv_ours_special("OLDPWD=", *env);
	if (!old)
		return (ft_putstr_fd("minishell: cd: OLDPWD not set\n", 2), 1);
	s = old->content;
	if (*(s + 7) == '\0')
		ft_printf("\n");
	else
	{
		if (chdir(old->content + 7))
			return (ft_putstr_fd("cd :", 2), ft_putstr_fd(old->content + 7, 2)
				, ft_putstr_fd(": ", 2), perror(NULL), 1);
		ft_printf("%s\n", old->content + 7);
	}
	join_and_export("PWD=", old->content + 7, env, "PWD=");
	join_and_export("OLDPWD=", lastdir, env, "PWD=");
	return (0);
}

int	ft_check_dir(char	*str)
{
	int		pid;
	char	n[PATH_MAX];
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		chdir(str);
		if (!getcwd(n, sizeof(n)))
			exit (1);
		else
			exit (0);
	}
	else
		waitpid(pid, &ret, 0);
	return (WEXITSTATUS(ret));
}
