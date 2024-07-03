/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 16:13:46 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/29 16:39:31 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int skip_n(char **cmd, int *ind)
{
	int i;
	int j;
	int s_i;

	i = 1;
	j = 1;
	s_i = i;
	while(cmd[i])
	{
		s_i = i;
		if (cmd[i][0] == '-')
		{
			while(cmd[i][j] == 'n')
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

int	ft_echo(t_exec *e, t_list *envp)
{
	(void) envp;
	int		x;
	int 	ind;

	ind = 0;
	x = skip_n(e->cmd, &ind);
	while (e->cmd[x] != NULL)
	{
		if (!ft_strncmp(e->cmd[x], "?", ft_strlen(e->cmd[x])))
			ft_printf("%d", e->ex);
		else
			ft_printf("%s", e->cmd[x]);
		if(e->cmd[x + 1] != NULL)
			ft_printf(" ");
		x++;
	}
	if (ind == 0)
		ft_printf("\n");
	return (0);
}
