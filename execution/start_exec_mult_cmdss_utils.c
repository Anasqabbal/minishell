/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_mult_cmdss_utils.c                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:35:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/28 19:29:05 by anqabbal         ###   ########.fr       */
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
			write(fd[1], e->here_doc[e->in_h_l - 1],
				ft_strlen(e->here_doc[e->in_h_l - 1]));
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, -1);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if (dup2(e->in[e->in_l - 1][0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, -1);
		close(e->in[e->in_l - 1][0]);
		e->in[e->in_l - 1][0] = -1;
	}
	return (lst->ex_code = 0, 0);
}

int	set_stdin(t_prs *lst, t_exec *e, int indice, int *fd)
{
	int	fd2[2];

	if (e->in)
		return (the_input(lst, e));
	else if ((!e->in && ft_prssize(lst) == 1 && indice))
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
		return (close(fd[0]), 0);
	}
	else if (!e->in && indice && ft_prssize(lst) != 1 && e->i)
	{
		if (!ft_is_pipe(0))
		{
			if (pipe(fd2) < 0)
				return (perror("pipe"), -1);
			if (dup2(fd2[0], STDIN_FILENO) < 0)
				return (perror("dup2"), -1);
			return (close(fd2[1]), close(fd2[0]), 0);
		}
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

int	dkchi_t3_signals(int *ret)
{
	int	r;

	r = 0;
	while (waitpid(-1, ret, 0) != -1)
	{
		if (WIFSIGNALED(*ret))
		{
			if (WTERMSIG(*ret) == SIGINT)
			{
				r = 130;
				g_sig = 0;
			}
			else if (WTERMSIG(*ret) == SIGQUIT)
			{
				r = 131;
				write(STDOUT_FILENO, "Quit: 3\n", 8);
			}
		}
		else
			r = WEXITSTATUS(*ret);
	}
	return (r);
}

int	ft_return(int *ret, int *i, t_all a)
{
	int				r;
	struct termios	s;

	r = 0;
	if (!(*ret))
	{
		r = dkchi_t3_signals(ret);
		tcsetattr(STDOUT_FILENO, TCSANOW, &s);
		signal(SIGINT, ft_handler);
		if (ft_export_(a.envp, NULL, NULL) < 0)
			return (*ret = 1, -1);
		return (r);
	}
	else
	{
		while (waitpid(-1, i, 0) != -1)
			;
		if (ft_export_(a.envp, NULL, NULL) < 0)
			return (*ret = 1, -1);
		return (*ret);
	}
}
/* malloc insied set_and_open */

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
		if (!ft_is_pipe(0))
		{
			if (pipe(fd2) < 0)
				return (perror("pipe"), -1);
			if (dup2(fd2[0], STDIN_FILENO) < 0)
				return (perror("dup2"), -1);
			return (close(fd2[1]), close(fd2[0]), 0);
		}
		a->indice = 1;
		return (1);
	}
	if (pipe((a)->fd) < 0)
		return (perror("pipe"), -1);
	return (0);
}
