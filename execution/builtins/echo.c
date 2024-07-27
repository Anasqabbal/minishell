/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:13:46 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/27 10:49:57 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	skip_n(char **cmd, int *ind)
{
	int	i;
	int	j;
	int	s_i;

	i = 1;
	while (cmd[i])
	{
		s_i = i;
		j = 1;
		if (cmd[i][0] == '-' && cmd[i][j])
		{
			while (cmd[i][j] && cmd[i][j] == 'n')
				j++;
			if (cmd[i][j] != '\0')
				return (s_i);
			*ind = 1;
		}
		else
			break ;
		i++;
	}
	return (i);
}

static void	print_all(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
	{
		ft_printf("%c", s[i]);
	}
}

int	ft_echo(t_exec *e, t_list *envp)
{
	int		x;
	int		ind;

	(void) envp;
	ind = 0;
	if (it_is_with_options(e->cmd + 1, 0, "echo"))
		return (1);
	x = skip_n(e->cmd, &ind);
	while (e->cmd[x] != NULL)
	{
		print_all(e->cmd[x]);
		ft_printf(" ");
		x++;
	}
	if (ind == 0)
		ft_printf("\n");
	return (0);
}
