/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:18:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/24 14:56:06 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calcul_strs(char *s1, char **s2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s2 && s2[i])
	{
		if (!ft_strncmp(s2[i], s1, ft_strlen(s1)))
			count++;
		i++;
	}
	return (count);
}

int	file_here_docs(char **f, t_exec *e, t_list **env, int *ret)
{
	int	i;
	int	len;
	int	j;

	i = -1;
	j = 0;
	len = calcul_strs("<<", f);
	if (len == 0)
		return (0);
	else if (len > 15)
		return (ft_putstr_fd("minishell :maximum here-document count exceeded\n"
				, 2), exit(2), 1);
	e->here_doc = malloc(sizeof(char *) * (len + 1));
	if (!e->here_doc)
		return (-1);
	while (f && f[++i])
	{
		if (!ft_strncmp(f[i], "<<<", ft_strlen(f[i])) && ft_strlen(f[i]) >= 2)
		{
			e->here_doc[j] = read_from_here_doc(f, i, env, ret);
			j++;
		}
	}
	return (e->in_h_l = len, e->here_doc[len] = NULL, 0);
}

static int	compare_and_check(char **f, t_exec *e,	int i)
{
	if (!ft_strncmp(f[i], "<", ft_strlen(f[i])))
	{
		if (check_file_access(f[i + 1], 1))
			return (1);
		if (e->in)
			to_free_f(e->in, 1);
		if (open_in_files(e, 1, f[i + 1], f[i]))
			return (1);
	}
	else if (!ft_strncmp(f[i], ">", ft_strlen(f[i]))
		|| !ft_strncmp(f[i], ">>", ft_strlen(f[i])))
	{
		if (e->out)
			to_free_f(e->out, 1);
		if (open_out_files(e, 1, f[i + 1], f[i]))
			return (1);
	}
	return (0);
}

int	set_and_open(t_exec *e, char **f, int i)
{
	while (f && f[++i])
	{
		if (!ft_strncmp(f[i], "<<", 2) && ft_strlen(f[i]) == 2)
		{
			e->in = malloc(sizeof(int *) * 1);
			if (!e->in)
				return (-1);
			e->in[0] = malloc(sizeof(int));
			if (!e->in[0])
				return (-1);
			e->in[0][0] = -1;
			e->in_f = 2;
			continue ;
		}
		if (compare_and_check(f, e, i))
			return (1);
	}
	return (0);
}

int	set_here_doc(t_prs *l, t_exec **e, t_list **env, int *ret)
{
	t_prs	*l2;
	t_exec *new;
	int		i;

	l2 = l;
	i = -1;
	while (l)
	{
		new = ft_exec_new();
		if (!new)
			return (1);
		if (file_here_docs(l->red, new, env, ret))
			return (-1);
		ft_execadd_back(e, new);
		l = l->next;
	}/* here in this case you need to check the ambiguous redirections for the bothe the infile and the outfile */
	while (l2)
	{
		while (l2 && l2->red && l2->red[++i])
		{
			if (ft_strncmp(l2->red[i], "<<", 2)
				&& !ft_strncmp(l2->red[i], "<", ft_strlen(l2->red[i])))
				check_file_access(l2->red[i + 1], 0);
		}
		l2 = l2->next;
		i = -1;
	}
	return (0);
}
