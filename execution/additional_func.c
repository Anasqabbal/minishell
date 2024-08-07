/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_func.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/04 10:22:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/07 12:50:54 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve3(int in, int out)
{
	if (out != -1 && dup2(out, STDOUT_FILENO) < 0)
		return (perror("dup2"), -1);
	if (out != -1)
		close(out);
	if (in != -1 && dup2(in, STDIN_FILENO) < 0)
		return (perror("dup2"), -1);
	if (in != -1)
		close (in);
	return (0);
}

int	ft_prssize(t_prs *lst)
{
	int		i;
	t_prs	*cur;

	if (lst == NULL)
		return (0);
	cur = lst;
	i = 0;
	while (cur != NULL)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}

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

int	it_is_signals11(int *ret)
{
	int	r;
	int	s;

	(void) ret;
	while (waitpid(-1, &s, 0) != -1)
	{
		if (WIFSIGNALED(s))
		{
			if (WTERMSIG(s) == SIGINT)
			{
				write(STDOUT_FILENO, "\n", 1);
				r = 130;
				g_sig = 0;
			}
			else if (WTERMSIG(s) == SIGQUIT)
			{
				r = 131;
				write(STDOUT_FILENO, "Quit: 3\n", 8);
			}
		}
		else
			r = WEXITSTATUS(s);
	}
	return (r);
}
