/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:20:04 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/25 16:10:30 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(char **opts, t_list *node)
{
	if (it_is_with_options(opts, 1, "env"))
		return (1);
	while (node)
	{
		if (!ft_strncmp("_=", node->content, 2))
		{
			node = node->next;
			continue ;
		}
		if (ft_strchr(node->content, '='))
			ft_printf("%s\n", node->content);
		node = node->next;
	}
	return (0);
}
