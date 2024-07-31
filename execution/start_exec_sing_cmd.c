/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_sing_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:27 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/31 17:58:23 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_(t_list **env, char **str, t_exec *e)
{
	char	*res1;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (str && str[i + 1])
		i++;
	if (str)
	{
		if ((!ft_strncmp(str[i], "$?", 2)) && ft_strlen(str[i]) == 2)
			return (export_exit_code(env, e));
		if (ft_strchr(str[i], '='))
			return (export_with_equal(str[i], env));
		res1 = my_strjoin("_=", str[i]);
	}
	else
		res1 = my_strjoin("_=", NULL);
	if (!res1)
		return (-1);
	if (!export1(res1, env))
		return (free(res1), -1);
	return (free(res1), 0);
}

int	initialize_sing(t_prs **lst, t_list **env, t_exec *e, t_sing *s)
{
	s->save = dup(STDOUT_FILENO);
	if (s->save < 0)
		return (perror("dup"), -1);
	s->out = -1;
	s->in = -1;
	s->ret = 0;
	s->envp = env;
	s->lst = *lst;
	s->e = e;
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
	if (s->e->out && !s->ret)
		s->out = s->e->out[s->e->out_l - 1][0];
	s->e->cmd = prepare_cmd((*lst)->cmd, (*lst)->opts, (*lst)->arg);
	if (!s->e->cmd)
		return (-1);
	if (from_lst_to_2d(envp, &(s->e->env)) && !s->ret)
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
	s->ret = ft_execve1(e, -1, s->out, 0);
	if (ft_prssize(*lst) == 1)
		s->ret = it_is_signals(&(s->ret));
	signal(SIGINT, ft_handler);
	return (s->ret);
}

int	one_cmd(t_prs **lst, t_list **envp, t_exec *e, char **path)
{
	t_sing	s;

	if (initialize_sing(lst, envp, e, &s))
		return (close(s.save), -1);
	s.ret = first_work(lst, envp, &s, path);
	if (s.ret == -1)
		return (close(s.save), -1);
	if (s.ret)
		return (close(s.save), s.ret);
	if (ft_export_(envp, e->cmd, e) < 0)
		return (close(s.save), -1);
	if (s.ret)
		return (close(s.save), s.ret);
	if (it_is_builtin((*lst)->cmd))
	{
		if (execute_this(lst, envp, e, &s) < 0)
			return (close(s.save), 1);
	}
	else
	{
		ft_execve3(s.in, s.out);
		s.ret = execvecmd(e, envp, path, lst);
	}
	ft_restore_output(s.out, s.save);
	return (close(s.save), s.ret);
}
