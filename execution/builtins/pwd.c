/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:48:57 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/06 10:40:25 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



int ft_pwd(t_list *env, char **str)
{
	(void)env;
	(void)str;
	char fpwd[PATH_MAX];

	getcwd(fpwd, sizeof(fpwd));
	ft_printf("%s\n", fpwd);
	return (0);
}