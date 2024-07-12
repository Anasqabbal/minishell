/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_ft2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:40:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/07 17:14:07 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_2dprint(char **str)
{
	int	i;

	if (!str)
		return (ft_printf("your 2D is NULL\n"), 1);
	else
	{
		i = 0;
		if (str[i])
		{
			while (str[i])
			{
				ft_printf("str[%d] = %s\n",i, str[i]);
				i++;
			}
			ft_printf("str[%d] = %s\n",i, str[i]);
		}
		else
			ft_printf("your str[%d] == NULL\n", i);
	}
	return (0);
}