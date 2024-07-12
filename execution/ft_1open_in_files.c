/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/12 16:34:26 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*9 functions*/
int		**to_free_f(int **file, int len)
{
	if (file)
	{
		while(file && --len >= 0)
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

static int	check_file_access(char *file, int indice)
{
	if (file)
	{
		if (!access(file, F_OK))
		{
			if (!access(file, R_OK))
				return (0);
			else
			{
				if (indice == 1)
					return (1);
				else
					return (ft_error_files(13, 1, file));
			}
		}
		else
		{
			if (indice == 1)
				return (1);
			else
				return (ft_error_files(2, 1, file)); //file not found;
		}
	}
	return (0);
}
static char	*read_from_here_doc(char **red, int i, char *lim, char *res)
{
	char	*here_doc;
	char	*tmp;

	here_doc = NULL;
	while(1 && red && red[i])
	{
		lim = red[i + 1];
		write(1, "> ", 2);
		res = get_next_line(0);
		if (!res || (!ft_strncmp(res, lim, ft_strlen(res) - 1) && (ft_strlen(res) - 1)))
			break ;
		tmp = here_doc;
		here_doc = my_strjoin(here_doc, res);
		if (!here_doc)
			return (free(tmp), free(res), NULL);
		free(res);
		free(tmp);
	}
	return (free(res), here_doc);
}

int	open_in_files(t_exec *e, int len, char *file, char *token)
{
	int	i;

	i = -1;
	e->in = malloc(sizeof(int *) * (len + 1));
	if (!e->in)
		return (1);// malloc failed;
	while(++i < len)
	{
		e->in[i] = malloc(sizeof(int));
		if (!e->in[i])
			return(e->in = to_free_f(e->in, i), 1); //free malloc before return; malloc failed;
		if (!ft_strncmp(token, "<<", 2))
			e->in[i][0] = -1;
		else if (!ft_strncmp(token, "<", 1))
			e->in[i][0] = creat_open_file(file, 0, 0);
		if ((ft_strncmp(token, "<<", 2) && e->in[i][0] == -1))
			return (to_free_f(e->in, i), 1);
	}
	e->in_f = 1;
	return (e->in_l = 1, 0);
}

int	to_free_m(char **f, int len)
{
	int	i;

	i = 0;
	if (f)
	{
		i = 0;
		while(i < len)
		{
			free(f[i]);
			i++;
		}
	}
	free(f);
	return (1);
}

int	calcul_strs(char *s1, char **s2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while(s2 && s2[i])
	{
		if (!ft_strncmp(s2[i], s1, ft_strlen(s1)))
			count++;
		i++;
	}
	return (count);
}

int	file_here_docs(char **f, t_exec *e)
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
		return (1); // malloc failed;
	while (f && f[++i])
	{
		if (!ft_strncmp(f[i], "<<", 2) && ft_strlen(f[i]) == 2)
		{
			e->here_doc[j] = read_from_here_doc(f, i, NULL, NULL);
			j++;
		}
	}
	return (e->in_h_l = len, e->here_doc[len] = NULL, 0);
}

int		set_and_open(t_exec *e, char **f, int i)
{
	while (f && f[++i])
	{
		if (!ft_strncmp(f[i], "<<", 2))
		{
			e->in = malloc(sizeof(int *) * 1);
			e->in[0] = malloc(sizeof(int));
			e->in[0][0] = -1;
			e->in_f = 2;
			continue ;
		}
		if (!ft_strncmp(f[i], "<", ft_strlen(f[i])))
		{
			if (check_file_access(f[i + 1], 1))
				return (1);
			if (e->in)
				to_free_f(e->in, 1);
			if (open_in_files(e, 1, f[i + 1], f[i]))
				return (1);
		}
		else if(!ft_strncmp(f[i], ">", ft_strlen(f[i]))
			|| !ft_strncmp(f[i], ">>", ft_strlen(f[i])))
		{
			if (e->out)
				to_free_f(e->out, 1);
			if (open_out_files(e, 1, f[i + 1], f[i]))
				return (1);
		}
	}
	return (0);
}

int	set_here_doc(t_prs *l, t_exec **e, int i)
{
	t_exec	*new;
	t_prs	*l2;

	l2 = l;
	while (l)
	{
		new = ft_exec_new();
		if (!new)
			return (1) ;/* when allocation failed free the previouse sttufs */
		if (file_here_docs(l->red, new))
			return (1); //free the previouse allocation for exec//
		ft_execadd_back(e, new);
		l = l->next;
	}
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
