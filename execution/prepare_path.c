/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_path.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/12 15:54:03 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/22 17:03:13 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int ft_error2(char *from, int indice)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(from, 2);
	if (indice == 127)
		ft_putstr_fd(": No such file or directory\n", 2);
	return (indice);
}

static int	valid_path(char *cmd, char *content, t_exec *p)
{
	char *cmd1;
	char *path;
	
	cmd1 = ft_strjoin("/", cmd);
	if (!cmd1)
		return(1); // allocation failed
	path = ft_strjoin(content, cmd1);
	if (!path)
		return (free(cmd1), 1); //allocation failed
	if (!access(path, F_OK))
	{
		if (access(path, X_OK) == -1)
			return (free(path), free(cmd1), ft_error(cmd, 126));
		else
			return (free(cmd1), p->path = path, 0);
	}
	return (free(path), free(cmd1), 999);
}

static int check_access1(char *cmd, char *content, t_exec *p)
{
	int		ret;
	char	**res;
	int		i;

	i = 0;
	res = ft_split(content + 1, ':');
	if (!res)
		return (1); //split failed; //allocation failed
	while (res[i])
	{
		ret = valid_path(cmd, res[i], p);
		if (!ret)
		{
			split_free(res, split_strlen(content, ':', 0));
			return (0);
		}
		else if (ret != 999)
		{
			split_free(res, split_strlen(content, ':', 0));
			return (ret);
		}
		i++;
	}
	split_free(res, split_strlen(content, ':', 0));
	return (ft_error(cmd, 127));
}

int		check_access(char *cmd, t_exec *p, t_list *env)
{
	t_list *res;

	if (!cmd)
		return(p->path = NULL, 0);
	if (!ft_strchr(cmd, '/'))
	{
		res = ft_getenv_ours("PATH=", env);
		if (!res)
			return (ft_error2(cmd, 127));
		return (check_access1(cmd, ft_strchr(res->content, '='), p));
	}
	if (!access(cmd, F_OK))
	{
		if (access(cmd, X_OK) == -1)
			return (ft_error(cmd, 126));
		else
		{
			p->path = ft_strdup(cmd);
			if (!p->path)
				return (1); // allocation failed;
			return (0);
		}
	}
	return (ft_error2(cmd, 127));
}

// int main(int ac, char **av, char **env)
// {
// 	t_prs p;
// 	t_list *envp;


// 	if (ac == 1)
// 		return (ft_printf("the number of args is not enough\n"), 1);
// 	{
// 		p.path = NULL;
// 		envp = ft_envdup(env);
// 		if (!envp)
// 			return (1);
		
// 		int res = check_access(av[1], &p, envp);
// 		printf("your path is %s and res %d\n", p.path, res);
// 		free(NULL);
// 		return (res);
// 	}
// }
