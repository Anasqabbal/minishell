/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_functions.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/03 12:55:21 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/27 15:14:00 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


t_exec *ft_exec_new(void)
{
    t_exec *new;

    new = malloc(sizeof(t_exec));
    if (!new)
        return (printf("return\n\n"), NULL);
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
    return (new);
}

void    ft_execadd_back(t_exec **h, t_exec *nw)
{
    t_exec *tmp;

    if (!h)
        return ;
    if (!(*h))
    {
        *h = nw;
        return ;
    }
    tmp = *h;
    while(tmp->n)
        tmp = tmp->n;
    tmp->n = nw;
}

void	ft_print_exec(t_exec *e)
{
	(void)e;
	if (!e->in)
		printf("your e->in is NULL\n");
	printf("the len of in_l == %d\n", e->in_l);
	if(!e->out)
		printf("your e->out is NULL\n");
	printf("the len of out_l == %d\n", e->out_l);
	if(e->cmd)
		ft_2dprint(e->cmd);
	if (e->path)
		printf("your path == %s", e->path);
	if (e->env)
		ft_2dprint(e->env);
	if(e->here_doc)
		ft_2dprint(e->here_doc);
	else
		printf("your here_doc is NULL\n");
	printf("the size == %d\n", e->size);

	printf("\n\n\n");
	
}

// int main()
// {
//       t_exec *h;
//       t_exec *nw;

//         h = NULL;
//       nw = ft_exec_new();
//       if (!nw)
//         return (1);
//     //ft_print_exec(nw); 
//     ft_execadd_back(&h, nw);
//     while (h)
//     {
//         ft_print_exec(h);  
//        h = h->n;
//     }
    
// }

