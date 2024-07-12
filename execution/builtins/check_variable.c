/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:19:08 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/08 16:38:38 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	var_error(char *from, char *str, int indice)
{
	ft_putstr_fd(from, 2);
	if (indice == 0)
		ft_putstr_fd(": not a valid identifier: ", 2);
	ft_putendl_fd(str, 2);
}

int	allowed_char(char c, char *allowed)
{
	int	i;
	int len;
	int ind;

	i = 0;
	len = ft_strlen(allowed);
	ind = 0;
	while(i < len)
	{
		if (c == allowed[i])
			ind = 1;
		i++;
	}
	return (ind);
}

int	valid_name(char *from, char *str, t_par *par)
{
	int		i;

	i = -1;
	if (!str || str[0] == '\0')
	{
		var_error(from, str, 0);
		return (0);
	}
	while (str[++i] && i < par->len - 1)
	{
		if ((i == 0 && !allowed_char(str[i], par->first))
		|| (i != 0 && !allowed_char(str[i], par->mid)))
			return (0);
	}
	if ((i == par->len - 1 && !allowed_char(str[i], par->last)))
		return (0);
	if (str[i] == '+' && ft_strchr(str, '='))
		return (1);
	else if (str[i] == '+' && !ft_strchr(str, '='))
		return (0);
	return (1);
}
