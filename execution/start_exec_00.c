/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/24 16:40:14 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "errno.h"

static int exec_builtins(t_prs *lst, t_list *envp)
{
	if (!ft_strncmp("export", lst->cmd, ft_strlen(lst->cmd)))
		return(ft_export(lst->arg, envp));
	else if (!ft_strncmp("env", lst->cmd, ft_strlen(lst->cmd)))
		return(ft_env(envp));
	else if (!ft_strncmp("cd", lst->cmd, ft_strlen(lst->cmd)))
		return(printf("do cd\n"), 0);
	else if (!ft_strncmp("unset", lst->cmd, ft_strlen(lst->cmd)))
		return(printf("do unset\n"), 0);
	else if (!ft_strncmp("exit", lst->cmd, ft_strlen(lst->cmd)))
		return(ft_exit(envp), 0);
	else if (!ft_strncmp("echo", lst->cmd, ft_strlen(lst->cmd)))
		return(printf("do echo\n"), 0);
}

static int	it_is_builtin(t_prs *lst, t_list *envp)
{
	(void)envp;
	if (!lst->cmd)
		return (1);
	if (!ft_strncmp("export", lst->cmd, ft_strlen(lst->cmd)))
		return(0);
	else if (!ft_strncmp("env", lst->cmd, ft_strlen(lst->cmd)))
		return(0);
	else if (!ft_strncmp("cd", lst->cmd, ft_strlen(lst->cmd)))
		return(0);
	else if (!ft_strncmp("unset", lst->cmd, ft_strlen(lst->cmd)))
		return(0);
	else if (!ft_strncmp("exit", lst->cmd, ft_strlen(lst->cmd)))
		return(0);
	else if (!ft_strncmp("echo", lst->cmd, ft_strlen(lst->cmd)))
		return(0);
	else
		return (1);
}


	/* check if you have one command or multiple commands 
		if one
			work with the it as thed last command;
		else
			enter to will and work with all with pipe;
	*/

int		start_exec(t_prs *lst, t_list *envp)
{
	t_exec e;
	int		ret;

	/* in this part you need to open the necessary files that you will need during the execution */
	// ret = ft_open_files(lst, &e); /* first open the files and work with it*/
	// if (ret)
	// 	return (ret);
	// if (dup2(e.in, STDIN_FILENO) < 1)/*open the infiles that you will need in this part*/
	// 	return(perror("dup"), 1);
	while(lst->next)
	{
		if (it_is_builtin(lst, envp))
			ret = mid_cmds(lst, envp, &e);
		else
			ret = mid_blts(lst, envp);
		lst = lst->next;
	}
	// ret = ft_open_files(lst, &e); /* first open the files and work with it*/
	// if (ret)
	// 	return (ret);
	if (dup2(e.out, STDOUT_FILENO) < 1) /*also before the last command you need to open the files that you will need in this case the outfile and so one*/
		return(perror("dup"), 1);
	if (it_is_builtin(lst, envp))
		ret = last_cmds(lst, envp, &e);
	else
		ret = last_blts(lst, envp)
	return (ret);
}
