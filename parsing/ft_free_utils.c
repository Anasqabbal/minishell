/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 18:19:14 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/30 17:25:39 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_node(t_prs *node)
{
	if (!node)
		return ;
	if (node->cmd)
		free(node->cmd);
	if (node->opts)
		free_it(node->opts, arg_count(node->opts));
	if (node->arg)
		free_it(node->arg, arg_count(node->arg));
	if (node->red)
		free_it(node->red, arg_count(node->red));
	free(node);
}

void	free_list(t_prs *head)
{
	t_prs	*tmp;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free_node(tmp);
	}
}

void	free_it_h(char **splt_pip, char *com, t_prs **head)
{
	free(com);
	free_list(*head);
	free_it(splt_pip, arg_count(splt_pip));
	exit(1);
}

void	free_it_h2(char **splt_pip, char *com, t_prs **head, t_prs *new)
{
	free(com);
	free_list(*head);
	free_it(splt_pip, arg_count(splt_pip));
	free(new);
	exit(1);
}

void	free_it(char **arg, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
