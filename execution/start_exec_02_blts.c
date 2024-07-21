/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_02_blts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:09 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/21 13:22:52 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*1 function*/

int	execvecmd(t_exec *e, t_list **envp, char **path, t_prs **l)
{
	int		ret;
	char	**var;

	ret = 0;
	var = e->cmd;
	if (!ft_strncmp("export", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_export(e->cmd + 1, envp);
	if (!ft_strncmp("env", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_env(e->cmd + 1, *envp);
	if (!ft_strncmp("echo", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_echo(e, *envp);
	if (!ft_strncmp("exit", e->cmd[0],
			ft_strlen(e->cmd[0])) && printf("exit\n"))
		ret = ft_exit(e, envp, l);
	if (!ft_strncmp("unset", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_unset(var + 1, envp, path);
	if (!ft_strncmp("cd", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_cd(var + 1, envp, *path);
	if (!ft_strncmp("pwd", e->cmd[0], ft_strlen(e->cmd[0])))
		ret = ft_pwd(*envp, e->cmd + 1);
	return (ret);
}

int	ft_execve2(t_exec *e, int in, int out, t_list **envp)
{
	int		pid;

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
		exit (execvecmd(e, envp, NULL, NULL));
	}
	else if (pid)
	{
		if (in != -1 && dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2(1)"), 1);
		if (in != -1)
			close(in);
	}
	return (0);
}

int	it_is_builtin(char *cmd)
{
	if (!cmd)
		return (1);
	if (!ft_strncmp("export", cmd, 6) && ft_strlen(cmd) == 6)
		return (0);
	else if (!ft_strncmp("env", cmd, 3) && ft_strlen(cmd) == 3)
		return (0);
	else if (!ft_strncmp("cd", cmd, 2) && ft_strlen(cmd) == 2)
		return (0);
	else if (!ft_strncmp("unset", cmd, 5) && ft_strlen(cmd) == 5)
		return (0);
	else if (!ft_strncmp("exit", cmd, 4) && ft_strlen(cmd) == 4)
		return (0);
	else if (!ft_strncmp("echo", cmd, 4) && ft_strlen(cmd) == 4)
		return (0);
	else if (!ft_strncmp("pwd", cmd, 3) && ft_strlen(cmd) == 3)
		return (0);
	else
		return (1);
}
