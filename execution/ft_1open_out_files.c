/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_out_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:28 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/27 16:54:23 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_restore_input(void)
{
	int	fd2;

	close(0);
	fd2 = open("/dev/tty", O_RDONLY);
	if (fd2 < 0)
		return (-1);
	return (0);
}

int	ft_restore_output(int out, int save)
{
	if (out != -1)
	{
		close(1);
		if (dup2(save, 1) < 1)
			return (perror("dup2 failed"), 1);
	}
	return (0);
}

int	creat_open_file(char *f1, int ind, int VAL)
{
	int	fd;

	if (ind == 0)
		fd = open(f1, O_RDONLY);
	else
		fd = open(f1, O_RDWR | VAL | O_CREAT, 0644);
	if (fd < 0)
		return (-1);
	return (fd);
}

int	open_out_files(t_exec *e, int len, char *file, char *token)
{
	int	i;

	i = -1;
	e->out = 0;
	e->out = malloc(sizeof(int *) * len);
	if (!e->out)
		return (-1); /* return -1 when malloc failure */
	while (++i < len)
	{
		if (check_ambiguous(file, 0))
			return (1);
		e->out[i] = malloc(sizeof(int));
		if (!e->out[i])
			return (to_free_f(e->out, i), -1); /* return -1 when malloc failure */
		if (!ft_strncmp(token, ">>", 2) && ft_strlen(token) == 2)
			e->out[i][0] = creat_open_file(file, 1, O_APPEND);
		else if (!ft_strncmp(token, ">", 1) && ft_strlen(token) == 1)
			e->out[i][0] = creat_open_file(file, 1, O_TRUNC);
		if (e->out[i][0] < 0)
			return (e->out = to_free_f(e->out, i), -1); /* return -1 when open failure */
	}
	return (e->out_l = 1, 0);
}
