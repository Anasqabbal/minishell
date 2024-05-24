/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_01_cmds.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/24 18:02:35 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int ft_execve1(t_exec *e, int in, int out)
{
	int pid;

	// if (!e->path && !e->cmd)
	// 	printf("all are NULL\n");
	pid  = fork();
	if (pid == 0)
	{
		close(in);
		if (dup2(out, STDOUT_FILENO) < 0)
			return (perror("dup2"), 1);
		close(out);
		execve(e->path, e->cmd, e->env);
	}
	else if (pid)
	{
		if (dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2"), 1);
		close(in);
		wait(NULL);
	}
	return (0);
}

// int	first_cmd(t_prs *lst, t_list *envp, t_exec *e)
// {
// 	ret = ft_open_files(lst, e);
// 	if (ret)
// 		return (ret);
// 	if (e->in)
// 	{
// 		if (!ft_strncmp(e->in[e->in_l][0], "<<", 2))
// 			write(0, )
// 	}
// }

int mid_cmds(t_prs *lst, t_list *envp, t_exec *e)
{
	int 	ret;
	int		fd[2];

	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	ret = ft_open_files(lst, e);
	if (ret)
		return (ret);
	ret = check_access(lst->cmd, e, envp);
	if (ret)
		return (ret);
	e->cmd = prepare_cmd(lst->cmd, lst->opts, lst->arg);
	e->env = from_lst_to_2d(envp);
	if (!e->env)
		return(printf("Error inside ft_exeve \n"), 1);// malloc failed
	return (ft_execve1(e, fd[0], fd[1]));
}

int last_cmds(t_prs *lst, t_list *envp, t_exec *e)
{
	int 	ret;
	// int		fd[2];

	// if (pipe(fd) < 0)
	// 	return (perror("pipe"), 1);
	ret = check_access(lst->cmd, e, envp);
	if (ret)
		return (ret);
	e->cmd = prepare_cmd(lst->cmd, lst->opts, lst->arg);
	e->env = from_lst_to_2d(envp);
	if (!e->env)
		return(printf("Error inside ft_exeve 2\n"), 1);// malloc failed
	return (ft_execve1(e, 0, e->out));
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

