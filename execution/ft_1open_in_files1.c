/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:18:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/28 19:19:38 by anqabbal         ###   ########.fr       */
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
			if (!e->here_doc[j])
				return (-1);
			if (g_sig == 1)
			{
				e->here_doc[j] = NULL;
				return (1);
			}
			j++;
		}
	}
	return (e->in_h_l = len, e->here_doc[len] = NULL, 0);
}

static int	compare_and_check(char **f, t_exec *e,	int i)
{
	int	ret;

	if (!ft_strncmp(f[i], "<", ft_strlen(f[i])))
	{
		if (check_file_access(f[i + 1], 1, 0))
			return (1);
		if (e->in)
			to_free_f(e->in, 1);
		if (open_in_files(e, 1, f[i + 1], f[i]))
			return (-1);
	}
	else if (!ft_strncmp(f[i], ">", ft_strlen(f[i]))
		|| !ft_strncmp(f[i], ">>", ft_strlen(f[i])))
	{
		if (check_file_access(f[i + 1], 1, 1))
			return (1);
		if (e->out)
			to_free_f(e->out, 1);
		ret = open_out_files(e, 1, f[i + 1], f[i]);
		if (ret == -1)
			return (-1);
		else if (ret)
			return (1);
	}
	return (0);
}

int	set_and_open(t_exec *e, char **f, int i)
{
	int		r;

	while (f && f[++i])
	{
		if ((!ft_strncmp(f[i], "<<", 2) && ft_strlen(f[i]) == 2)
			|| (!ft_strncmp(f[i], "<<<", 3) && ft_strlen(f[i]) == 3))
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
		r = compare_and_check(f, e, i);
		if (r == 1)
			return (1);
		else if (r == -1)
			return (-1);
	}
	return (0);
}

int	set_here_doc(t_prs *l, t_exec **e, t_list **env, int *ret)
{
	t_prs	*l2;
	t_exec	*new;
	int		i;

	l2 = l;
	while (l)
	{
		new = ft_exec_new();
		if (!new)
			return (-1);
		if (file_here_docs(l->red, new, env, ret) == -1)
			return (-1);
		ft_execadd_back(e, new);
		l = l->next;
	}
	while (l2)
	{
		i = -1;
		while (l2 && l2->red && l2->red[++i])
		{
			if (ft_strncmp(l2->red[i], "<<", 2)
				&& !ft_strncmp(l2->red[i], "<", 1))
			{
				if (check_file_access(l2->red[i + 1], 0, 0))
					break ;
			}
			else if (!ft_strncmp(l2->red[i], ">>", 2)
				|| !ft_strncmp(l2->red[i], ">", 1))
			{
				if (check_file_access(l2->red[i + 1], 0, 1))
					break ;
			}
		}
		l2 = l2->next;
	}
	return (0);
}
