/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_02_blts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:09 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/29 16:52:48 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*1 function*/

int		execvecmd(t_exec *e, t_list **envp, char **path)
{
	int		ret;

	ret = 0;
	if (!ft_strncmp("export", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_export(e->cmd + 1, envp);
	if (!ft_strncmp("env", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_env(*envp);
	if (!ft_strncmp("echo", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_echo(e, *envp);
	if (!ft_strncmp("exit", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_exit(e, envp);
	if (!ft_strncmp("unset", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_unset(e->cmd + 1, envp, path);
	if (!ft_strncmp("cd", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_cd(e->cmd + 1, *envp, *path);
	return (ret);
}

int		ft_execve2(t_exec *e, int in, int out, t_list **envp)
{
	int		pid;
	int		ret;

	ret = 0;
	pid = fork();
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
		exit (execvecmd(e, envp, NULL));
	}
	else if (pid)
	{
		if (in != -1 && dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2(1)"), 1);
		if (in != -1)
			close(in);
		return (ret);
	}
	return (0);
}

int	it_is_builtin(char *cmd)
{
	if (!ft_strncmp("export", cmd, ft_strlen(cmd)))
		return(0) ;
	else if (!ft_strncmp("env", cmd, ft_strlen(cmd)))
		return(0) ;
	else if (!ft_strncmp("cd", cmd, ft_strlen(cmd)))
		return(0) ;
	else if (!ft_strncmp("unset", cmd, ft_strlen(cmd)))
		return(0) ;
	else if (!ft_strncmp("exit", cmd, ft_strlen(cmd)))
		return(0) ;
	else if (!ft_strncmp("echo", cmd, ft_strlen(cmd)))
		return(0) ;
	else
		return (1);
}