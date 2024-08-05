/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_mult_cmdss_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:35:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/05 08:47:30 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	the_input(t_prs *lst, t_exec *e)
{
	int	fd[2];

	if (!lst->red)
		return (0);
	if (e->in_f == 2)
	{
		if (pipe(fd) < 0)
			return (perror("pipe"), -1);
		if (e->here_doc[e->in_h_l - 1])
			ft_putstr_fd(e->here_doc[e->in_h_l - 1], fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if (dup2(e->in[e->in_l - 1][0], STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
		close(e->in[e->in_l - 1][0]);
		e->in[e->in_l - 1][0] = -1;
	}
	return (0);
}

int	set_stdout_and_cmd(t_prs *l, t_exec *e, int *o, int *fd)
{
	if (e->out)
	{
		*o = e->out[0][0];
		close(fd[1]);
	}
	if (!e->out && ft_prssize(l) != 1)
		*o = fd[1];
	e->cmd = prepare_cmd(l->cmd, l->opts, l->arg);
	if (!e->cmd)
		return (-1);
	return (0);
}

int	it_is_signals(int *ret, t_all *a, int i, int s)
{
	int	r;

	while (waitpid(a->l_pid[++i], &s, 0) != -1)
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
	if ((*ret))
		r = *ret;
	return (r);
}

int	ft_return(int *ret, int *i, t_all a)
{
	int				r;

	r = 0;
	(void)i;
	r = it_is_signals(ret, &a, -1, 0);
	signal(SIGINT, ft_handler);
	if (ft_export_(a.envp, NULL, NULL) < 0)
		return (*ret = 1, -1);
	return (r);
}

int	open_files_and_pipe(t_all *a)
{
	int	ret;
	int	fd2[2];

	a->out = -1;
	ret = set_and_open((a)->e, (a)->p->red, -1);
	if (ret)
	{
		if (ret < 0)
			return (-1);
		(a)->p = (a)->p->next;
		(a)->e = (a)->e->n;
		if (!ft_is_pipe(0, 0))
		{
			if (pipe(fd2) < 0)
				return (perror("pipe"), -1);
			if (dup2(fd2[0], STDIN_FILENO) < 0)
				return (perror("dup2"), -1);
			return (close(fd2[1]), close(fd2[0]), 1);
		}
		a->indice = 1;
		return (1);
	}
	if (pipe((a)->fd) < 0)
		return (perror("pipe"), -1);
	return (0);
}
