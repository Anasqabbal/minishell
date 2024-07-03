/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 14:20:04 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/28 09:31:54 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_env(t_list *node)
{
	static int i;

	while (node)
	{
		ft_printf("%s\n", node->content);
		node = node->next;
	}
	if (i++ != 0)
		ft_printf("_=/builtins/env\n");
	return (0);
}
