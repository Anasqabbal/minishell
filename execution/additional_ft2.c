/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_ft2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:40:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/04 10:15:25 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_2dprint(char **str)
{
	int	i;

	if (!str)
		return (printf("your 2D is NULL\n"), 1);
	else
	{
		i = 0;
		if (str[i])
		{
			while (str[i])
			{
				printf("%s\n", str[i]);
				i++;
			}
		}
		else
			printf("your str[%d] == NULL\n", i);
	}
	return (0);
}