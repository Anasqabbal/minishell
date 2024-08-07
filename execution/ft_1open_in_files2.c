/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:24:25 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/05 17:55:52 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	first_work(char **f, t_exec *e, int *i, int *j)
{
	int	len;

	*i = -1;
	*j = 0;
	len = calcul_strs("<<", f);
	if (len == 0)
		return (0);
	else if (len > 15)
		return (ft_putstr_fd("minishell :maximum here-document count exceeded\n"
				, 2), 1);
	e->here_doc = ft_calloc(sizeof(char *), (len + 1));
	if (!e->here_doc)
		return (-1);
	e->in_h_l = len;
	return (99);
}

int	file_here_docs(char **f, t_exec *e, t_list **env, int *ret)
{
	int	i;
	int	j;
	int	rett;

	rett = first_work(f, e, &i, &j);
	if (rett != 99)
		return (rett);
	while (f && f[++i])
	{
		if (!ft_strncmp(f[i], "<<<", ft_strlen(f[i])) && ft_strlen(f[i]) >= 2)
		{
			e->here_doc[j] = read_from_here_doc(f, i, env, ret);
			if (!e->here_doc[j])
				return (-1);
			if (g_sig == 1)
				return (e->here_doc[j] = NULL, 1);
			j++;
		}
	}
	return (e->here_doc[e->in_h_l] = NULL, 0);
}

char	*add_new_line(char **res)
{
	char	*tmp;

	tmp = my_strjoin(*res, "\n");
	if (!tmp)
		return (NULL);
	free(*res);
	return (*res = tmp);
}
