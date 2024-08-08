/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_sing_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:27 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/08 14:37:35 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	complete_first_work(t_sing *s, t_prs **lst, t_list **envp)
{
	if (s->e->out && !s->ret)
		s->out = s->e->out[s->e->out_l - 1][0];
	s->e->cmd = prepare_cmd((*lst)->cmd, (*lst)->opts, (*lst)->arg);
	if (!s->e->cmd)
		return (-1);
	if (from_lst_to_2d(envp, &(s->e->env)) == -1 && !s->ret)
		return (-1);
	return (0);
}

int	first_work(t_prs **lst, t_list **envp, t_sing *s, char **path)
{
	if (g_sig == 1)
		return (1);
	s->ret = set_and_open(s->e, (*lst)->red, -1);
	if (s->ret == -1)
		return (-1);
	else if (s->ret == 1)
		return (1);
	if (!(*lst)->cmd)
		return (0);
	s->ret = check_access((*lst)->cmd, s->e, envp, *path);
	if (!(*lst)->cmd)
		return ((*lst)->ex_code = s->ret, 0);
	if (s->ret == -1)
		return (-1);
	if (s->e->in && !s->ret)
	{
		if (the_input(*lst, s->e) < 0)
			return ((*lst)->ex_code = 1, -1);
	}
	if (complete_first_work(s, lst, envp) == -1)
		return (-1);
	return (s->ret);
}

static int	execute_this(t_prs **lst, t_list **envp, t_exec *e, t_sing *s)
{
	if (!(*lst)->cmd)
		return (0);
	if (!strncmp((*lst)->cmd, "./minishell", 11)
		&& !ft_getenv_ours("SHLVL=", *envp))
	{
		if (!export1("SHLVL=1", envp))
			return (-1);
	}
	s->ret = ft_execve1(e, -1, s->out, NULL);
	if (ft_prssize(*lst) == 1)
		s->ret = it_is_signals11(&(s->ret));
	signal(SIGINT, ft_handler);
	return (s->ret);
}

static int	one_cmd_exe(t_sing *s, t_list **envp, t_prs **lst, char **path)
{
	if (it_is_builtin((*lst)->cmd))
	{
		if (execute_this(lst, envp, s->e, s) < 0)
			return (close(s->save), -1);
	}
	else
	{
		if (ft_execve3(s->in, s->out) == -1)
			return (-1);
		s->ret = execvecmd(s->e, envp, path, lst);
	}
	return (0);
}

int	one_cmd(t_prs **lst, t_list **envp, t_exec *e, char **path)
{
	t_sing	s;

	if (initialize_sing(lst, envp, e, &s))
		return (close(s.save), -1);
	s.ret = first_work(lst, envp, &s, path);
	if (s.ret == -1)
		return (close(s.save), -1);
	if (ft_export_(envp, e->cmd, e) < 0)
		return (close(s.save), -1);
	if (s.ret || !(*lst)->cmd)
		return (close(s.save), s.ret);
	if (s.ret)
		return (close(s.save), s.ret);
	if (one_cmd_exe(&s, envp, lst, path) == -1)
		return (-1);
	if (ft_restore_output(s.out, s.save) == -1)
		return (-1);
	return (close(s.save), s.ret);
}
