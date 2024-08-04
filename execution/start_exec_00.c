/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/04 10:24:49 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_child(int in, int out, t_exec *e)
{
	signal(SIGQUIT, SIG_DFL);
	if (in != -1)
		close(in);
	if (out != -1 && dup2(out, STDOUT_FILENO) < 0)
		return (perror("dup2"), -1);
	if (out != -1)
		close(out);
	if (execve(e->path, e->cmd, e->env) < 0)
		return (perror("execve"), -1);
	return (0);
}

static int	small_check(int *pid, t_all *a, int *in, t_exec *e)
{
	if (*pid < 0 && ++(a->pr))
	{
		if ((a->pr) == 1)
			perror("fork");
		return (close((*in)), e->fo = -2, 1);
	}
	return (0);
}

int	ft_execve1(t_exec *e, int in, int out, t_all *a)
{
	int			pid;

	signal(SIGINT, ft_handler_fork);
	pid = fork();
	if (small_check(&pid, a, &in, e))
		return (1);
	if (a && a->pi != 1024)
		a->l_pid[a->pi++] = pid;
	if (pid == 0)
	{
		if (inside_child(in, out, e))
			return (-1);
	}
	else if (pid)
	{
		if (in != -1 && dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
		if (in != -1)
			close(in);
	}
	return (0);
}

int	single_and_multiple_cmds(t_prs **lst, t_list **envp, t_exec *e, char **path)
{
	int				ret;
	struct termios	ss;

	tcgetattr(STDOUT_FILENO, &ss);
	if (ft_prssize(*lst) != 1)
	{
		ret = mult_cmds(*lst, envp, e, path);
		if (ret == -1)
			return (tcsetattr(STDOUT_FILENO, TCSANOW, &ss), ret);
	}
	else
	{
		ret = one_cmd(lst, envp, e, path);
		if (ret == -1 || ft_restore_input() < 0)
			return (tcsetattr(STDOUT_FILENO, TCSANOW, &ss), -1);
	}
	tcsetattr(STDOUT_FILENO, TCSANOW, &ss);
	return (ret);
}

int	start_exec(t_prs **lst, t_list **envp, int rett, char **path)
{
	t_exec			*e;
	int				ret;

	e = NULL;
	ret = rett;
	if (set_here_doc(*lst, &e, envp, &rett) == -1)
		return (ft_clear_exec(&e), ft_lstclear(envp, free),
			clear_prs(lst), exit(1), 1);
	if (*lst)
	{
		e->ex = rett;
		ret = single_and_multiple_cmds(lst, envp, e, path);
		if (ret == -1)
			return (ft_clear_exec(&e), ft_lstclear(envp, free),
				clear_prs(lst), exit(1), 1);
	}
	else
		if (!export1("_=", envp))
			return (ft_lstclear(envp, free), clear_prs(lst), exit(1), 1);
	return (ft_clear_exec(&e), ret);
}
