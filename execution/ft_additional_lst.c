/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_additional_lst.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 09:44:32 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/23 11:02:33 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*2 functions*/

int	ft_lstget_pos(char *str, t_list *lst)
{
	char	*tmp1;
	int		j;
	int		i;

	tmp1 = NULL;
	if (ft_strchr(str, '+'))
		tmp1 = remove_plus(str, tmp1);
	if (tmp1)
		printf("after remove + your content became === %s\n", tmp1);
	i = 0;
	while (lst)
	{
		j = -1;
		if (!tmp1)
		{
			while(str[++j] && str[j] != '=')
				;
			if (!ft_strncmp(lst->content, str, j))
				return (i);
		}
		else if (tmp1)
		{
			while(tmp1[++j] && tmp1[j] != '=')
				;
			 if (!ft_strncmp(lst->content, tmp1, j))
				return (i);
		}
		lst = lst->next;
		i++;
	}
	return (-1);
}

void	*it_is_0(t_list **lst, t_list *s1, t_list *s2)
{
	s2->next = (*lst)->next;
	ft_lstdelone(s1, free);
	*lst = s2;
	return (s2);
}

void	*ft_lstremplace(t_list **lst, t_list *s1, t_list *s2)
{
	t_list	*prev;
	t_list	*next;
	t_list	*n;
	int		pos;
	int		i;

	n = *lst;
	prev = NULL;
	pos = ft_lstget_pos(s1->content, n);
	if (pos == -1)
		return (NULL);
	if (pos == 0)
		return (it_is_0(lst, s1, s2));
	i = -1;
	while (++i < pos)
	{
		if (i == pos - 1)
			prev = n;
		n = (n)->next;
	}
	next = (n)->next;
	if (prev)
		prev->next = s2;
	ft_lstdelone(n, free);
	return (s2->next = next, s2);
}
