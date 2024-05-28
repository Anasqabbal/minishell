/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 12:50:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/28 15:08:01 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include "errno.h"

int ft_is_pipe(int fd) 
{
    struct stat st;

    if (fstat(fd, &st) == -1) {
        perror("fstat");
        return -1;  // An error occurred
    }

    if (S_ISFIFO(st.st_mode)) {
        return 1;  // It's a pipe
    } else {
        return 0;  // It's not a pipe
    }
}

// static int exec_builtins(t_prs *lst, t_list *envp)
// {
// 	if (!ft_strncmp("export", lst->cmd, ft_strlen(lst->cmd)))
// 		return(ft_export(lst->arg, envp));
// 	else if (!ft_strncmp("env", lst->cmd, ft_strlen(lst->cmd)))
// 		return(ft_env(envp));
// 	else if (!ft_strncmp("cd", lst->cmd, ft_strlen(lst->cmd)))
// 		return(printf("do cd\n"), 0);
// 	else if (!ft_strncmp("unset", lst->cmd, ft_strlen(lst->cmd)))
// 		return(printf("do unset\n"), 0);
// 	else if (!ft_strncmp("exit", lst->cmd, ft_strlen(lst->cmd)))
// 		return(ft_exit(envp), 0);
// 	else if (!ft_strncmp("echo", lst->cmd, ft_strlen(lst->cmd)))
// 		return(printf("do echo\n"), 0);
// 	return (0);
// }


	/* check if you have one command or multiple commands 
		if one
			work with the it as thed last command;
		else
			enter to will and work with all with pipe;
	*/

int	ft_prssize(t_prs *lst)
{
	int		i;
	t_prs	*cur;

	if (lst == NULL)
		return (0);
	cur = lst;
	i = 0;
	while (cur != NULL)
	{
		i++;
		cur = cur->next;
	}
	return (i);
}



int		start_exec(t_prs *lst, t_list *envp)
{
	t_exec e;
	int		ret;
	int		i;
	(void) ret;
	(void) envp;
	(void) e;

	i = 1;
	e.size = ft_prssize(lst);
	if (e.size != 1)
	{
		ret = mult_cmds(lst, envp, &e);
		if (ret)
			return (ret);
	}
	else
		one_cmd(lst, envp, &e);
	return (lst->ex_code);
}
