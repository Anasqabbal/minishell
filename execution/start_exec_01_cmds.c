/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_01_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/14 11:31:26 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*4 functions*/

// int t_l(char **h)
// {
// 	int	i;

// 	i = 0;
// 	if (!h)
// 		return (0);
// 	if (!h[i])
// 		return (0);
// 	while(h && h[i])
// 		i++;
// 	return (i - 1);
// }

int	the_input(t_prs *lst, t_exec *e)
{
	int fd[2];

	if(!lst->red)
		return (0);
	if (e->in_f == 2)
	{
		if (pipe(fd) < 0)
			return (perror("pipe"), 1);
		if (e->here_doc[e->in_h_l - 1])
			write(fd[1], e->here_doc[e->in_h_l - 1], ft_strlen(e->here_doc[e->in_h_l - 1]));
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, 1);
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if (dup2(e->in[e->in_l - 1][0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, 1);
		close(e->in[e->in_l - 1][0]);
		e->in[e->in_l - 1][0] = -1;
	}
	return (lst->ex_code = 0, 0);
}

int		set_stdin(t_prs *lst, t_exec *e, int indice, int *fd)
{
	int fd2[2];

	if (e->in)
	{
		if (the_input(lst, e))
			return (lst->ex_code);
	}
	else if ((!e->in && ft_prssize(lst) == 1 && indice))
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return(perror("dup2"), 1);
		return(close(fd[0]), 0);
	}
	else if (!e->in && indice && ft_prssize(lst) != 1 && e->i)
	{
		if (!ft_is_pipe(0))
		{
			if(pipe(fd2) < 0)
				return (perror("pipe"), 1);
			if (dup2(fd2[0], STDIN_FILENO) < 0)
				return(perror("dup2"), 1);
			return (close(fd2[1]), close(fd2[0]), 0);
		}
	}
	return (0);
}
void	set_stdout_and_cmd(t_prs *l, t_exec *e, int *o, int *fd)
{
	if (e->out)
	{
		*o = e->out[0][0];
		close(fd[1]);
	}
	if (!e->out && ft_prssize(l) != 1)
		*o = fd[1];
	e->cmd = prepare_cmd(l->cmd, l->opts, l->arg);
}

int	one_cmd(t_prs **lst, t_list **envp, t_exec *e, char **path)
{
	int		ret;
	int		out;
	int		in;
	int		save;

	save = dup(STDOUT_FILENO);
	if (save < 0)
		return (1);
	out = -1;
	in = -1;
	if (set_and_open(e, (*lst)->red, -1))
		return (close(save), (*lst)->ex_code = 1);
	ret = check_access((*lst)->cmd, e, *envp, *path);
	if (ret || !(*lst)->cmd)
		return (close(save), (*lst)->ex_code = ret);
	if (e->in)
	{
		if (the_input(*lst, e))
			return (close(save), (*lst)->ex_code);
		in = e->in[e->in_l - 1][0];
		dup2(in, STDIN_FILENO);
	}
	if (e->out)
		out = e->out[e->out_l - 1][0];
	e->cmd = prepare_cmd((*lst)->cmd, (*lst)->opts, (*lst)->arg);
	if (from_lst_to_2d(*envp, &(e->env)))
		return(close(save), 1);
	if (it_is_builtin((*lst)->cmd))
	{
		if (!strncmp((*lst)->cmd, "./minishell", 11) && !ft_getenv_ours("SHLVL=", *envp))
			export1("SHLVL=1", envp);
		ret = ft_execve1(e, -1, out);
		if (ft_prssize(*lst) == 1)
			waitpid(-1, &ret, 0);
		ret = WEXITSTATUS(ret);
	}
	else
	{
		ft_execve3(in, out);
		ret = execvecmd(e, envp, path, lst);
	}
	ft_restore_output(out, save);
	if (ft_restore_input() < 0)
		return (1);
	close(save);
	return (ret);
}

int	ft_return (int *ret, int *i)
{
	if (!(*ret))
	{
			while(waitpid(-1, ret, 0) != -1)
				;
		return (WEXITSTATUS(*ret));
	}
	else
	{
		while(waitpid(-1, i, 0) != -1)
			;
		return (*ret);
	}
}

int	mult_cmds(t_prs *lst, t_list **envp, t_exec *e, char **path)
{
	int		ret;
	int		out;
	int		fd[2];
	int		indice;
	int		i;

	i = 0;
	while (lst)
	{
		e->i = i;
		e->ex = WEXITSTATUS(ret);
		out = -1;
		ret = set_and_open(e, lst->red, -1); //open files -----------------------------------------------------------------------------*/
		if (ret)
		{
			lst = lst->next;
			e = e->n;
			continue;
		}
		if (pipe(fd) < 0)
			return (perror("pipe"), 1);
		ret = check_access(lst->cmd, e, *envp, *path); //it is not bultins command and before failed commmand -------------------------*/
		if ((ret || !lst->cmd) &&  it_is_builtin(lst->cmd))
		{
			indice = 1;
			lst = lst->next;
			e = e->n;
			close(fd[0]);
			close(fd[1]);
			if (ft_restore_input() < 0)
				return (1);
			continue ;
		}
		ret = set_stdin(lst, e, indice, fd); ///set stdin and stdout -----------------------------------------------------------       */
		if (ret)
			return (ret);
		set_stdout_and_cmd(lst, e, &out, fd);
		if (from_lst_to_2d(*envp, &(e->env)))
			return(printf("Error inside ft_exeve \n"), 1);
		if (ft_prssize(lst) != 1) //execution ---------------------------------------------------------------------                    */
		{
			if (it_is_builtin(lst->cmd))
				ret = ft_execve1(e, fd[0], out);
			else
				ret = ft_execve2(e, fd[0], out, envp);
			if (ft_is_pipe(out))
				close(out);
		}
		else
		{
			close(fd[0]);
			close(fd[1]);
			if (it_is_builtin(lst->cmd))
				ret = ft_execve1(e, -1, out);
			else
				ret = ft_execve2(e, -1, out, envp);
			ft_restore_input();
		}
		lst = lst->next;
		e = e->n;
		indice = 0;
		i++;
	}
	return(ft_return(&ret, &i));
}
/* this function with 63 in real*/