/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/31 17:56:17 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_ambiguous(char *str, int ind)
{
	int	i;

	i = -1;
	if (ind == 0)
	{
		while (str[++i] && str[i] != '$')
			;
		if (str[i] == '$')
			return (1);
		return (0);
	}
	else
	{
		ft_putstr_fd("minishell :", 2);
		ft_putstr_fd(str, 2);
		ft_putstr_fd(": ambiguous redirect\n", 2);
		return (1);
	}
}

static int	complete_work(char *file, int indice, int outfile)
{
	if (!access(file, R_OK) && !outfile)
		return (0);
	else if (!outfile)
	{
		if (indice == 1)
			return (1);
		else
			return (ft_error_files(13, 1, file));
	}
	if (!access(file, W_OK) && outfile)
		return (0);
	else
	{
		if (indice == 1)
			return (1);
		else
			return (ft_error_files(13, 1, file));
	}
}

int	check_file_access(char *file, int indice, int outfile)
{
	if (file)
	{
		if (file[0] == '\0')
		{
			if (indice == 1)
				return (1);
			else
				return (ft_error_files(2, 1, file));
		}
		if (check_ambiguous(file, 0) && !indice)
			return (check_ambiguous(file, 1));
		if (!access(file, F_OK))
			return (complete_work(file, indice, outfile));
		else if (!outfile)
		{
			if (indice == 1)
				return (1);
			else
				return (ft_error_files(2, 1, file));
		}
	}
	return (0);
}

int	open_in_files(t_exec *e, int len, char *file, char *token)
{
	int	i;

	i = -1;
	e->in = malloc(sizeof(int *) * (len + 1));
	if (!e->in)
		return (-1);
	while (++i < len)
	{
		e->in[i] = malloc(sizeof(int));
		if (!e->in[i])
			return (e->in = to_free_f(e->in, i), -1);
		if (!ft_strncmp(token, "<<", 2))
			e->in[i][0] = -1;
		else if (!ft_strncmp(token, "<", 1))
			e->in[i][0] = creat_open_file(file, 0, 0);
		if ((ft_strncmp(token, "<<", 2) && e->in[i][0] == -1))
			return (e->in = to_free_f(e->in, i), -1);
	}
	e->in_f = 1;
	return (e->in_l = 1, 0);
}

int	set_stdin(t_prs *lst, t_exec *e, int indice, int *fd)
{
	int	fd2[2];

	if (e->in)
		return (the_input(lst, e));
	else if ((!e->in && ft_prssize(lst) == 1 && indice))
	{
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), -1);
		return (close(fd[0]), 0);
	}
	else if (!e->in && indice && ft_prssize(lst) != 1 && e->i)
	{
		if (!ft_is_pipe(0))
		{
			if (pipe(fd2) < 0)
				return (perror("pipe"), -1);
			if (dup2(fd2[0], STDIN_FILENO) < 0)
				return (perror("dup2"), -1);
			return (close(fd2[1]), close(fd2[0]), 0);
		}
	}
	return (0);
}
