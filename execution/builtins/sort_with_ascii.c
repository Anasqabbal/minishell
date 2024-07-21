/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_with_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:25:28 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/16 15:55:12 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_swap(t_list *n)
{
	char	*tmp;
	t_list	*next;

	next = n->next;
	tmp = n->content;
	n->content = next->content;
	next->content = tmp;
	return (1);
}

static int	ft_lstcmp(t_list *n)
{
	char	*s1;
	char	*s2;
	int		len;

	if (!n->next)
		return (1);
	s1 = n->content;
	s2 = n->next->content;
	len = ft_strlen(n->content);
	if (ft_strncmp(s1, s2, len) < 0)
		return (1);
	else
		return (0);
}

static int	ft_check(t_list *n)
{
	while (n)
	{
		if (ft_lstcmp(n))
			n = n->next;
		else
			return (0);
	}
	return (1);
}

int	ft_sort_ascii(t_list *n)
{
	t_list	*head;

	head = n;
	if (ft_check(n))
		return (1);
	while (n)
	{
		if (!ft_lstcmp(n))
		{
			ft_swap(n);
			ft_sort_ascii(head);
		}
		n = n->next;
	}
	return (1);
}
