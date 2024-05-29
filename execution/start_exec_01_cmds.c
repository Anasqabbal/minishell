/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_01_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/29 17:18:07 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execve1(t_exec *e, int in, int out, int *ret)
{
	int		pid;

	pid  = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (in != -1)
			close(in);
		if (out != -1 && dup2(out, STDOUT_FILENO) < 0)
			return (perror("dup2(0)"), 1);
		if (out != -1)
			close(out);
		if (execve(e->path, e->cmd, e->env) < 0)
			return(perror("execve"), 1);
	}
	else if (pid)
	{
		if (in != -1 && dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2(1)"), 1);
		if (in != -1)
			close(in);
		return (waitpid(pid ,ret, 0), WEXITSTATUS(*ret));
	}
	return (0);
}

int  the_input(t_prs *lst, t_exec *e)
{
	int fd[2];

	if (!ft_strncmp(lst->in[e->in_l - 1], "<<", 2))
	{
		if (pipe(fd) < 0)
				return (perror("pipe"), 1); //close all files and free them;
		if (e->here_doc)
			write(fd[1], e->here_doc, ft_strlen(e->here_doc));
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, 1);// close files descriptores and free its memory
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		if(dup2(e->in[e->in_l - 1][0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, 1); // close files descriptores and free its memory
		close(e->in[e->in_l - 1][0]);
		e->in[e->in_l - 1][0] = -1;
	}
	return (lst->ex_code = 0, 0);
}

int	one_cmd(t_prs *lst, t_list *envp, t_exec *e)
{
	int		ret;
	int		out;

	printf("ONE\n");
	out = -1;
	ret = check_access(lst->cmd, e, envp);
	if (ret)
		return (lst->ex_code = ret);
	if (ft_open_files(lst, e))
		return (lst->ex_code = 1);
	if (e->in)
	{
		if (the_input(lst, e))
			return (lst->ex_code);
	}
	if (e->out)
		out = e->out[e->out_l - 1][0];
	e->cmd = prepare_cmd(lst->cmd, lst->opts, lst->arg);
	e->env = from_lst_to_2d(envp);
	if (!e->env)
		return(printf("from_lst_to_2d failed\n"), 1);
	ret = ft_execve1(e, -1, out, &ret);
	if (ft_restore_input())
		return(1);
	return (ret);
}

int mult_cmds(t_prs *lst, t_list *envp, t_exec *e)
{
	int		ret;
	int		out;
	int		fd[2];
	int		fd2[2];
	int		indice;
	int		first_size;

	first_size = ft_prssize(lst);
	indice = 0;
	lst->ex_code = 0;
	ret = 99;
	while(lst)
	{
		// printf("ther return of your commad %d\n", ret);
		//ft_printf("the size of your lst == %d\n",ft_prssize(lst));
		out = -1;
		ret = ft_open_files(lst, e);
		if (ret)
			return (ret);
		if (pipe(fd) < 0)
			return (perror("pipe"), 1);
		ret = check_access(lst->cmd, e, envp);
		if (ret)
		{
			indice = 1;
			lst = lst->next;
			close(fd[0]);
			close(fd[1]);
			//ft_clear_exec(e);
			ft_restore_input();
			continue;
		}
		if (e->in)
		{
			if (the_input(lst, e))
				return (lst->ex_code);
		}
		else if ((!e->in && ft_prssize(lst) == 1 && indice))
		{
			if (dup2(fd[0], STDIN_FILENO) < 0)
				return(perror("dup2"), 1);
				close(fd[0]);
		}
		else if (!e->in && indice && ft_prssize(lst) != 1)
		{
			if (!ft_is_pipe(0))
			{
				if(pipe(fd2) < 0)
					return (perror("pipe"), 1);
				if (dup2(fd2[0], STDIN_FILENO) < 0)
					return(perror("dup2"), 1);
				close(fd2[0]);
				close(fd2[1]);
			}
		}
		if (e->out)
		{
			out = e->out[e->out_l - 1][0];
			close(fd[1]);
		}
		if (!e->out && ft_prssize(lst) != 1)
			out = fd[1];
		e->cmd = prepare_cmd(lst->cmd, lst->opts, lst->arg);
		e->env = from_lst_to_2d(envp);
		if (!e->env)
			return(printf("Error inside ft_exeve \n"), 1);// malloc failed
		if (ft_prssize(lst) != 1)
		{
			printf("MID\n");
			ret = ft_execve1(e, fd[0], out, &ret);
			if (ft_is_pipe(out))// the return value if ft_is_pipe
				close(out);
		}
		else
		{
			printf("LAST\n");
			close(fd[1]);
			ret = ft_execve1(e, -1, out, &ret);
		}
		// if (ft_is_pipe(1))
		// 	printf("your STDOUT is pipe\n");
		ft_clear_exec(e);
		lst = lst->next;
		indice = 0;
	}
	printf("ther return of your commad %d\n", ret);
	if (ft_restore_input())
		return (1);
	return (ret);
}


