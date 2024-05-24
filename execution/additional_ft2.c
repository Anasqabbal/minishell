/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_ft2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:40:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/15 17:00:11 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void to_free22(char **res)
{
	int i;

	i = -1;
	if (res)
	{
		while (res[++i])
			free(res[i]);
		free(res);
	}
}

char **from_lst_to_2d(t_list *s)
{
	char	**res;
	int		len;
	int		i;

	i = -1;
	len = ft_lstsize(s);
	if (!len)
		return (NULL);// your lst is 0;
	printf("the len of your list is %d\n", len);
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return(NULL); //malloc failed;
	while (++i < len && s)
	{
		res[i] = ft_strdup(s->content);
		if (!res[i])
			return (to_free22(res), NULL);
		s = s->next;
	}
	res[len] = NULL;

	// int j = 0;
	// while(j < len - 3)
	// {
	// 	printf("res[%d] == %s\n", j, res[j]);
	// 	j++;
	// }
	return (res);
}