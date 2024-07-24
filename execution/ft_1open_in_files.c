/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/24 14:59:07 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambiguous(char *str, int ind)
{
	int	i;

	i = 0;
	if (ind == 0)
	{
		if (str[i] == '$' && str[i + 1])
			return (1);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": anbuguous redirect\n", 2);
		return (1);
	}
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

int	check_file_access(char *file, int indice)
{
	if (file)
	{
		if (check_ambiguous(file, 0))
			return (check_ambiguous(file, 1));
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
				return (ft_error_files(2, 1, file));
		}
	}
	return (0);
}

char	*read_from_here_doc(char **red, int i, t_list **env, int *ret)
{
	char	*here_doc;
	char	*tmp;
	char	*res;
	char	*lim;

	here_doc = NULL;
	while (1 && red && red[i])
	{
		lim = red[i + 1];
		res = readline(">");
		if (!res || (!ft_strncmp(res, lim, ft_strlen(res))
				&& (ft_strlen(res) == ft_strlen(lim))) || lim[0] == '\0')
			break ;
		if (res[0] != '\0')
			add_history(res);
		tmp = here_doc;
		res = dollar_sign(res);
		res = cmd_expa(res, *env, ret);
		here_doc = my_strjoin(here_doc, res);
		if (!here_doc)
			return (free(tmp), free(res), exit(1), NULL);
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
		return (exit(1), 1);
	while (++i < len)
	{
		e->in[i] = malloc(sizeof(int));
		if (!e->in[i])
			return (e->in = to_free_f(e->in, i), exit(1), 1);
		if (!ft_strncmp(token, "<<", 2))
			e->in[i][0] = -1;
		else if (!ft_strncmp(token, "<", 1))
			e->in[i][0] = creat_open_file(file, 0, 0);
		if ((ft_strncmp(token, "<<", 2) && e->in[i][0] == -1))
			return (e->in = to_free_f(e->in, i), 1);
	}
	e->in_f = 1;
	return (e->in_l = 1, 0);
}

