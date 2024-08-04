/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:55:21 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/04 11:12:57 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	from_lst_to_2d(t_list **s1, char ***env)
{
	char	**res;
	int		len;
	int		i;
	t_list	*s;

	i = -1;
	s = *s1;
	len = ft_lstsize(s);
	if (!len)
		return (0);
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (-1);
	while (++i < len && s)
	{
		res[i] = ft_strdup((s)->content);
		if (!res[i])
			return (to_free(res), -1);
		s = (s)->next;
	}
	res[len] = NULL;
	*env = res;
	return (0);
}

t_exec	*ft_exec_new(void)
{
	t_exec	*new;

	new = malloc(sizeof(t_exec));
	if (!new)
		return (NULL);
	new->in = NULL;
	new->in_f = 0;
	new->in_l = 0;
	new->out = NULL;
	new->out_l = 0;
	new->cmd = NULL;
	new->path = NULL;
	new->env = NULL;
	new->here_doc = NULL;
	new->size = 0;
	new->n = NULL;
	new->ex = 0;
	new->i = 0;
	new->in_h_l = 0;
	new->fo = 0;
	new->p = 0;
	return (new);
}

void	ft_execadd_back(t_exec **h, t_exec *nw)
{
	t_exec	*tmp;

	if (!h)
		return ;
	if (!(*h))
	{
		*h = nw;
		return ;
	}
	tmp = *h;
	while (tmp->n)
		tmp = tmp->n;
	tmp->n = nw;
}
