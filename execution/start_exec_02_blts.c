/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_exec_02_blts.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 11:50:09 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/28 11:23:58 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	it_is_builtin(t_prs *lst, t_list *envp)
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