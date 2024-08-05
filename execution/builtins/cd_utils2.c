/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd_utils2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 09:41:45 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/05 13:11:25 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_do_cd(char **str, t_list **env)
{
	char	s[PATH_MAX];

	if (str[0][0] == '/')
		cd_absolute_path(str[0], env);
	else
	{
		if (ft_strnstr("..", str[0]
				, ft_strlen(str[0])) && ft_strlen(str[0]) % 2 == 0)
			return (move_back(str[0], env));
		cd_relative_path(str[0], env);
		getcwd(s, sizeof(s));
		if (join_and_export("PWD=", s, env, "PWD=") == -1)
			return (-1);
	}
	return (0);
}
