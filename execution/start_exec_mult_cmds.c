/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_mult_cmds.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/28 19:27:18 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* this indice for check the previouse command if is 
	failed or not here when the command is failed I fill the indice by 1*/

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

int	initialize_t_all(t_prs *p, t_list **envp, t_exec *e, t_all *a)
{
	a->p = p;
	a->e = e;
	a->envp = envp;
	a->ret = 0;
	a->out = -1;
	a->indice = 0;
	a->i = 0;
	return (0);
}

/*in the line 62 if sometest failed remmenber 
	you remove restore input from here*/

int	execute_this(t_all a)
{
	int	r;

	if (ft_prssize(a.p) != 1)
	{
		if (it_is_builtin((a.p)->cmd))
			a.ret = ft_execve1(a.e, a.fd[0], a.out, 0);
		else
			a.ret = ft_execve2(a.e, a.fd[0], a.out, a.envp);
		r = ft_is_pipe(a.out);
		if (r == 1)
			close(a.out);
	}
	else
	{
		close(a.fd[0]);
		close(a.fd[1]);
		if (it_is_builtin(a.p->cmd))
			a.ret = ft_execve1(a.e, -1, a.out, 0);
		else
			a.ret = ft_execve2(a.e, -1, a.out, a.envp);
		r = ft_restore_input();
	}
	if (r == -1 || a.ret == -1)
		return (a.ret = 1, -1);
	return (0);
}

int	complete_work(t_all *a)
{
	if (a->ret == -1)
		return (-1);
	a->ret = set_stdin(a->p, a->e, a->indice, a->fd);
	if (a->ret)
		return (a->ret = 1, -1);
	if (set_stdout_and_cmd(a->p, a->e, &(a->out), a->fd))
		return (-1);
	if (from_lst_to_2d(a->envp, &(a->e->env)) < 0)
		return (-1);
	if (execute_this(*a) < 0)
		return (-1);
	a->p = a->p->next;
	a->e = a->e->n;
	a->indice = 0;
	a->i++;
	return (0);
}

int	mult_cmds(t_prs *lst, t_list **envp, t_exec *e, char **path)
{
	t_all	a;

	if (g_sig == 1)
		return (1);
	initialize_t_all(lst, envp, e, &a);
	while (a.p)
	{
		a.e->i = a.i;
		a.e->ex = WEXITSTATUS(a.ret);
		a.ret = open_files_and_pipe(&a);
		if (a.ret == -1)
			return (-1);
		if (a.ret == 1)
			continue ;
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
