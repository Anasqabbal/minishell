/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_with_ascii.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/05 14:25:28 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/30 19:29:52 by anqabbal         ###   ########.fr       */
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
	int		res;

	if (!n->next)
		return (1);
	s1 = n->content;
	s2 = n->next->content;
	len = ft_strlen(n->content);
	res = ft_strncmp(s1, s2, len);
	if (res < 0 || !res)
		return (1);
	else
		return (0);
}

int	ft_sort_ascii(t_list *n1)
{
	t_list	*n;
	t_list	*head;

	ft_envdup_exept(n1, NULL, &n);
	head = n;
	while (n)
	{
		if (!ft_lstcmp(n))
		{
			ft_swap(n);
			n = head;
			continue ;
		}
		n = n->next;
	}
	ft_print_export(head, 0);
	ft_lstclear(&head, free);
	return (1);
}
