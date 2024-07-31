/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:00:18 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/31 17:09:53 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_clear_exec(t_exec **e)
{
	t_exec	*tmp;

	while (*e)
	{
		(*e)->in = to_free_f((*e)->in, (*e)->in_l);
		(*e)->out = to_free_f((*e)->out, (*e)->out_l);
		(*e)->cmd = to_free((*e)->cmd);
		free((*e)->path);
		(*e)->path = NULL;
		(*e)->env = to_free((*e)->env);
		(*e)->in_l = 0;
		(*e)->out_l = 0;
		(*e)->here_doc = to_free((*e)->here_doc);
		(*e)->size = 0;
		tmp = *e;
		*e = (*e)->n;
		free(tmp);
	}
	*e = NULL;
}

int	**to_free_f(int **file, int len)
{
	if (file)
	{
		while (file && --len >= 0)
		{
			if (file[len][0] >= 0)
				close (file[len][0]);
			free(file[len]);
			file[len] = NULL;
		}
		free(file);
	}
	return (NULL);
}

void	clear_prs(t_prs **c)
{
	t_prs	*tmp;

	while (c && *c)
	{
		if ((*c)->cmd)
		{
			free((*c)->cmd);
			(*c)->cmd = NULL;
		}
		if ((*c)->arg)
			(*c)->arg = to_free((*c)->arg);
		if ((*c)->opts)
			(*c)->opts = to_free((*c)->opts);
		if ((*c)->red)
			(*c)->red = to_free((*c)->red);
		tmp = *c;
		*c = (*c)->next;
		free(tmp);
	}
}
