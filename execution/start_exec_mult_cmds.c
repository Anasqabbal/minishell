/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_mult_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/02 14:57:50 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	inside_if(t_all *a)
{
	if (a->ret == -1)
		return (-1);
	a->indice = 1;
	a->p = a->p->next;
	a->e = a->e->n;
	close(a->fd[0]);
	close(a->fd[1]);
	if (ft_restore_input() < 0)
		return (-1);
	return (0);
}

int	execute_this(t_all *a)
{
	int	r;

	if (ft_prssize(a->p) != 1)
	{
		if (it_is_builtin((a->p)->cmd))
			a->ret = ft_execve1(a->e, a->fd[0], a->out, a);
		else
			a->ret = ft_execve2(a->e, a->fd[0], a->out, a->envp);
		r = ft_is_pipe(a->out, a->ret);
		if (r == 1)
			close(a->out);
	}
	else
	{
		close(a->fd[0]);
		close(a->fd[1]);
		if (it_is_builtin(a->p->cmd))
			a->ret = ft_execve1(a->e, -1, a->out, a);
		else
			a->ret = ft_execve2(a->e, -1, a->out, a->envp);
		r = ft_restore_input();
	}
	if (r == -1 || a->ret == -1)
		return (a->ret = 1, -1);
	return (0);
}

static int	complete_work(t_all *a)
{
	int	r;

	if (a->ret == -1)
		return (-1);
	a->ret = set_stdin(a->p, a->e, a->indice, a->fd);
	if (a->ret)
		return (a->ret = 1, -1);
	if (set_stdout_and_cmd(a->p, a->e, &(a->out), a->fd))
		return (-1);
	if (from_lst_to_2d(a->envp, &(a->e->env)) < 0)
		return (-1);
	r = execute_this(a);
	if (r == -1)
		return (r);
	if (a->e->fo == -2)
		a->ret = 1;
	a->p = a->p->next;
	a->e = a->e->n;
	a->indice = 0;
	a->i++;
	return (0);
}

static int	first_check(t_all *a)
{
	a->e->i = a->i;
	a->e->ex = WEXITSTATUS(a->ret);
	a->ret = open_files_and_pipe(a);
	if (a->ret == -1)
		return (-1);
	if (a->ret == 1)
		return (a->ret = 1, 1);
	if (!a->p)
		return (2);
	return (0);
}

int	mult_cmds(t_prs *lst, t_list **envp, t_exec *e, char **path)
{
	t_all	a;
	int		ret;

	if (initialize_t_all(lst, envp, e, &a))
		return (1);
	while (a.p && a.e->fo != -2)
	{
		ret = first_check(&a);
		if (ret == -1)
			return (-1);
		else if (ret == 1)
		{
			if (ft_restore_input())
				return (-1);
			continue ;
		}
		else if (ret == 2 || a.e->fo == -2)
			break ;
		a.ret = check_access(a.p->cmd, a.e, a.envp, *path);
		if ((a.ret || !a.p->cmd) && it_is_builtin(a.p->cmd))
		{
			if (inside_if(&a) < 0)
				return (-1);
			continue ;
		}
		if (complete_work(&a) < 0)
			return (-1);
	}
	return (ft_return(&a.ret, &a.i, a));
}
