/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_01_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/26 18:14:27 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execve1(t_exec *e, int in, int out)
{
	int pid;

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
		wait(NULL);
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
		write(fd[1], e->here_doc, ft_strlen(e->here_doc));
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, 1);// close files descriptores and free its memory
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		printf("the e->in[%d][0] == %d and its name is %s\n", (e->in_l - 1), e->in[e->in_l - 1][0], lst->in_f[e->in_l - 1]);
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
	int		in;
	int		out;

	in = -1;
	out = -1;
	ret = check_access(lst->cmd, e, envp);
	if (ret)
		return (ret);
	if (ft_open_files(lst, e))
		return (lst->ex_code);
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
		return(printf("Error inside ft_exeve \n"), 1);// malloc failed
	return (lst->ex_code = ft_execve1(e, in, out));
}

int mult_cmds(t_prs *lst, t_list *envp, t_exec *e)
{
	int		ret;
	int		fd[2];
	int		out;
	int		in;

	in = -1;
	out = -1;
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	ret = check_access(lst->cmd, e, envp);
	if (ret)
		return (ret);
	ret = ft_open_files(lst, e);
	if (ret)
		return (ret);
	if (e->in)
	{
		if (the_input(lst, e))
			return (lst->ex_code);
	}
	if (e->out)
	{
		out = e->out[e->out_l - 1][0];
		close(fd[1]);
	}
	if (!e->out)
		out = fd[1];
	e->cmd = prepare_cmd(lst->cmd, lst->opts, lst->arg);
	e->env = from_lst_to_2d(envp);
	if (!e->env)
		return(printf("Error inside ft_exeve \n"), 1);// malloc failed
	return (ft_execve1(e, fd[0], out));
}

int last_cmd(t_prs *lst, t_list *envp, t_exec *e)
{
	int 	ret;
	int		out;

	out = -1;
	ret = check_access(lst->cmd, e, envp);
	if (ret)
		return (ret);
	ret = ft_open_files(lst, e);
	if (ret)
		return (ret);
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
		return(printf("Error inside ft_exeve 2\n"), 1);// malloc failed
	return (ft_execve1(e, -1, out));
}

/*FIRST COMMAND*/
	/*INTPUT*/
		/*if the file doesn't exist you should consider the stdin as the input file*/

	/*OUTPUT*/
		/*if the file doesn't exist*/
		/*PIPE*/
			/* if there is a pipe you should conisder it as input for the next command */
			/* if not you should print your out on the screen */

/*MID COMMAND*/
	/*INPUT*/
		/*if the file doesn't exist you should consider the pipe as the input file*/
		/*if there is a file you should consider it as input file*/

	/*OUTPUT*/
		/*if the out file doesn't exist you should consider the pipe as the output_file*/
		/*if there is a file you should consider it as output_file*/

/*LAST COMMAND*/
	/*INPUT*/
		/*if the files doesn't exist you should consider the pipe as input file*/
		/*if there is a file you should consider it as input_file*/
	/*OUTPUT*/
		/*if the file doesn't exist you should consider the stdout as output_file*/
		/*if there is a file you should consider it as input*/

