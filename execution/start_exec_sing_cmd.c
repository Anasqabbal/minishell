/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_sing_cmd.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 11:43:27 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/27 18:10:25 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	export_exit_code(t_list **env, t_exec *e)
{
	char	*itoa_res;
	char	*res;

	itoa_res = ft_itoa(e->ex);
	if (!itoa_res)
		return (-1); /* DONE */
	res = my_strjoin("_=", itoa_res);
	if (!res)
		return (free(itoa_res), -1); /* DONE */
	if (!export1(res, env)) /* DONE */
		return (free(itoa_res), free(res), -1);
	return (free(itoa_res), free(res), 0);
}

int	export_with_equal(char *str, t_list **env)
{
	char	*res;
	char	*res1;
	char	*add;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (-1);
	add = ft_strchr(str, '+');
	if (add && add < ft_strchr(str, '='))
		len -= 1;
	while (++i < len)
		res[i] = str[i];
	res[i] = '\0';
	res1 = my_strjoin("_=", res);
	if (!res1)
		return (free(res), -1);
	if (!export1(res1, env))
		return (free(res), free(res1), -1);
	return (free(res), free(res1), 0);
}

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
			return (export_exit_code(env, e)); /* DONE */
		if (ft_strchr(str[i], '='))
			return (export_with_equal(str[i], env)); /* DONE */
		res1 = my_strjoin("_=", str[i]);
	}
	else
		res1 = my_strjoin("_=", NULL);
	if (!res1)
		return (-1); /* DONE */
	if (!export1(res1, env)) /* DONE */
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
	if (set_and_open(s->e, (*lst)->red, -1) == -1) /* DONE */
		return ((*lst)->ex_code = 1, -1);
	s->ret = check_access((*lst)->cmd, s->e, envp, *path); /* DONE */
	if (!(*lst)->cmd)
		return ((*lst)->ex_code = s->ret, 0);
	if (s->ret == -1)
		return (-1);
	if (s->e->in && !s->ret)
	{
		if (the_input(*lst, s->e) < 0) /* DONE */
			return ((*lst)->ex_code = 1, -1);
	}
	if (s->e->out && !s->ret)
		s->out = s->e->out[s->e->out_l - 1][0];
	s->e->cmd = prepare_cmd((*lst)->cmd, (*lst)->opts, (*lst)->arg); /* DONE */
	if (!s->e->cmd)
		return (-1);
	if (from_lst_to_2d(envp, &(s->e->env)) && !s->ret) /* DONE */
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
		s->ret = dkchi_t3_signals(&(s->ret));
	signal(SIGINT, ft_handler);
	return (s->ret);
}

int	one_cmd(t_prs **lst, t_list **envp, t_exec *e, char **path)
{
	t_sing	s;
	int		ret;

	if (initialize_sing(lst, envp, e, &s) < 0) /* DONE */
		return (close(s.save), -1);
	ret = first_work(lst, envp, &s, path); /* inide this */
	if (ret == -1)
		return (close(s.save), -1);
	if (ret)
		return (close(s.save), ret);
	if (ft_export_(envp, e->cmd, e) < 0) /* DONE */
		return (close(s.save), -1);
	if (ret)
		return (close(s.save), ret);
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
