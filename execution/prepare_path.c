/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:54:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/30 10:04:41 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*3 functions*/

static int	valid_path(char *cmd, char *content, t_exec *p)
{
	char	*cmd1;
	char	*path;

	cmd1 = ft_strjoin("/", cmd);
	if (!cmd1)
		return (-1);
	path = ft_strjoin(content, cmd1);
	if (!path)
		return (free(cmd1), -1);
	if (!access(path, F_OK))
	{
		if (access(path, X_OK) == -1)
			return (free(path), free(cmd1), ft_error(cmd, 126));
		else
			return (free(cmd1), p->path = path, 0);
	}
	return (free(path), free(cmd1), 999);
}

static int	check_access1(char *cmd, char *content, t_exec *p)
{
	int		ret;
	char	**res;
	int		i;

	i = 0;
	if (content)
	{
		res = ft_split(content + 1, ':');
		if (!res)
			return (-1);
		while (res[i])
		{
			ret = valid_path(cmd, res[i], p);
			if (!ret)
				return (to_free(res), 0);
			else if (ret == -1)
				return (to_free(res), -1);
			else if (ret != 999)
				return (to_free(res), 0);
			i++;
		}
		to_free(res);
	}
	return (ft_error(cmd, 127));
}

int	check_it_is_directory(char *cmd, t_exec *p, char *path)
{
	struct stat	s;

	(void)path;
	if (ft_strchr(cmd, '/'))
	{
		if (!access(cmd, F_OK))
		{
			if (stat(cmd, &s) < 0)
				return (perror("stat"), 1);
			if (S_ISDIR(s.st_mode))
				return (ft_error_p(cmd, 252));
			if (access(cmd, X_OK) == -1)
				return (ft_error_p(cmd, 126));
			p->path = ft_strdup(cmd);
			if (!p->path)
				return (-1);
			return (0);
		}
		return (ft_error_p(cmd, 127));
	}
	else
		return (0);
	return (0);
}

int	check_access(char *cmd, t_exec *p, t_list **env, char *path)
{
	t_list	*res;

	
	if (!cmd || !it_is_builtin(cmd))
		return (p->path = NULL, 0);
	if (cmd[0] == '\0')
		return (ft_error(cmd, 127));
	if (!ft_strchr(cmd, '/'))
	{
		if (cmd[0] == '.' && ft_strlen(cmd) == 1)
			return (ft_error_p(cmd, 2));
		if (path)
			return (check_access1(cmd,
					ft_strchr(path, '='), p));
		res = ft_getenv_ours("PATH=", *env);
		if (!res)
			return (ft_error_p(cmd, 127));
		return (check_access1(cmd,
				ft_strchr(res->content, '='), p));
	}
	else
		return (check_it_is_directory(cmd, p, path));
}
