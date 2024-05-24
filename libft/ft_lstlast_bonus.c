/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 15:36:51 by anqabbal          #+#    #+#             */
/*   Updated: 2023/11/27 13:06:37 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list	*ft_lstlast(t_list *lst)
{
	int		res;
	int		i;
	t_list	*cur;

	if (lst == NULL)
		return (0);
	cur = lst;
	res = ft_lstsize(cur);
	i = 0;
	while (i < res - 1 && cur != NULL)
	{
		cur = cur->next;
		i++;
	}
	return (cur);
}
