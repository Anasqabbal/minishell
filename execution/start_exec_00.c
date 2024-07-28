/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/28 19:25:07 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_execve1(t_exec *e, int in, int out, int pid)
{
	struct termios	s;

	tcgetattr(STDOUT_FILENO, &s);
	signal(SIGINT, ft_handler_fork);
	pid = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		signal(SIGQUIT, SIG_DFL);
		if (in != -1)
			close(in);
		if (out != -1 && dup2(out, STDOUT_FILENO) < 0)
			return (perror("dup2(0)"), 1);
		if (out != -1)
			close(out);
		if (execve(e->path, e->cmd, e->env) < 0)
			return (perror("execve(1)"), 1);
	}
	else if (pid)
	{
		if (in != -1 && dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2(1)"), 1);
		if (in != -1)
			close(in);
	}
	return (0);
}

int	ft_execve3(int in, int out)
{
	if (out != -1 && dup2(out, STDOUT_FILENO) < 0)
		return (perror("dup2"), 1);
	if (out != -1)
		close(out);
	if (in != -1 && dup2(in, STDIN_FILENO) < 0)
		return (perror("dup2"), 1);
	if (in != -1)
		close (in);
	return (0);
}

int	ft_is_pipe(int fd)
{
	struct stat	st;

	if (fd == -1)
		return (0);
	if (fstat(fd, &st) == -1)
		return (perror("fstat"), -1);
	if (S_ISFIFO(st.st_mode))
		return (1);
	else
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

int	start_exec(t_prs **lst, t_list **envp, int rett, char **path)
{
	t_exec	*e;
	int		ret;

	e = NULL;
	ret = rett;
	if (set_here_doc(*lst, &e, envp, &rett) == -1)
		return (ft_clear_exec(&e), ft_lstclear(envp, free), clear_prs(lst), exit(1), 1);
	if (*lst)
	{
		e->ex = rett;
		if (ft_prssize(*lst) != 1)
		{
			ret = mult_cmds(*lst, envp, e, path);
			if (ret < 0)
				return (ft_clear_exec(&e), ft_lstclear(envp, free), clear_prs(lst), exit(1), 1);
		}
		else
			ret = one_cmd(lst, envp, e, path);
		if (ret == -1 || ft_restore_input() < 0)
			return (ft_clear_exec(&e), ft_lstclear(envp, free), clear_prs(lst), exit(1), 1);
	}
	else
		if (!export1("_=", envp))
			return (ft_lstclear(envp, free), clear_prs(lst), exit(1), 1);
	return (clear_prs(lst), ft_clear_exec(&e), ret);
}
