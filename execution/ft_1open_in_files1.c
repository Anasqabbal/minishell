/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files1.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:18:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/03 20:24:32 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	compare_and_check(char **f, t_exec *e,	int i)
{
	if (!ft_strncmp(f[i], "<", ft_strlen(f[i]))
		|| (!ft_strncmp(f[i], "<(", ft_strlen(f[i]))))
	{
		if (check_file_access(f[i], f[i + 1], 1, 0))
			return (1);
		if (e->in)
			to_free_f(e->in, 1);
		if (open_in_files(e, 1, f[i + 1], f[i]))
			return (1);
	}
	else if (!ft_strncmp(f[i], ">", ft_strlen(f[i]))
		|| !ft_strncmp(f[i], ">>", ft_strlen(f[i]))
		|| (!ft_strncmp(f[i], ">(", ft_strlen(f[i])))
		|| (!ft_strncmp(f[i], ">>(", ft_strlen(f[i]))))
	{
		if (check_file_access(f[i], f[i + 1], 1, 1))
			return (1);
		if (e->out)
			to_free_f(e->out, 1);
		if (open_out_files(e, 1, f[i + 1], f[i]))
			return (1);
	}
	return (0);
}

int	complete_here_doc(t_exec *e)
{
	if (e->in)
		to_free_f(e->in, 1);
	e->in = malloc(sizeof(int *) * 1);
	if (!e->in)
		return (-1);
	e->in[0] = malloc(sizeof(int));
	if (!e->in[0])
		return (-1);
	e->in[0][0] = -1;
	e->in_f = 2;
	e->in_l = 1;
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
			if (complete_here_doc(e) == -1)
				return (-1);
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

static void	first_file_access_check(t_prs *l2)
{
	int		i;

	while (l2)
	{
		i = -1;
		while (l2 && l2->red && l2->red[++i])
		{
			if ((ft_strncmp(l2->red[i], "<<", 2)
					&& !ft_strncmp(l2->red[i], "<", 1))
				|| !ft_strncmp(l2->red[i], "<(", 2))
			{
				if (check_file_access(l2->red[i], l2->red[i + 1], 0, 0))
					break ;
			}
			else if (!ft_strncmp(l2->red[i], ">>", 2)
				|| !ft_strncmp(l2->red[i], ">", 1))
			{
				if (check_file_access(l2->red[i], l2->red[i + 1], 0, 1))
					break ;
			}
		}
		l2 = l2->next;
	}
}

int	set_here_doc(t_prs *l, t_exec **e, t_list **env, int *ret)
{
	t_prs	*l2;
	t_exec	*new;

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
	first_file_access_check(l2);
	return (0);
}
