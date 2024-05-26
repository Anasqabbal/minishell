/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/26 14:08:38 by anqabbal         ###   ########.fr       */
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
	int		i;

	i = 1;
	e.size = ft_lstsize(lst);
	lst = lst->next;
	if (e.size != 1 && !ret)
	{
		while(lst->next)
		{
			e.size = ft_lstsize(lst);
			ret = mult_cmds(lst, envp, &e);
			if (ret)
				return (ret);
			lst = lst->next;
			i++;
		}
		e.size = ft_lstsize(lst);
		ret = last_cmd(lst, envp, &e);
	}
	else
		one_cmd(lst, envp, &e);
	return (ret);
}
