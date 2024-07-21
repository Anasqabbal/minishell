/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_variable.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 16:19:08 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/18 15:17:20 by anqabbal         ###   ########.fr       */
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

void	ft_print_export(t_list *envp, int indice)
{
	char	*str;
	int		i;

	if (indice == 0)
	{
		while (envp)
		{
			str = envp->content;
			if (ft_strchr(str, '=') && !ft_strnstr(str, "_=", 2))
			{
				i = -1;
				ft_printf("declare -x ");
				while (str[++i] != '=')
					ft_printf("%c", str[i]);
				ft_printf("%c\"%s\"\n", str[i], (str + i + 1));
			}
			else if (!ft_strnstr(str, "_=", 2))
				ft_printf("declare -x %s\n", envp->content);
			envp = envp->next;
		}
	}
}

int	valide_par(char *from, char *str)
{
	t_par	par;

	par.first = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	par.mid = "abcdefghijklmnopqrstuvwxyz\
		ABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789=";
	par.last = "abcdefghijklmnopqrstuvwxyz\
		ABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789=+";
	if (str)
	{
		if (!ft_strchr(str, '='))
			par.len = ft_strlen(str);
		else
			par.len = ft_strlen(str) - (ft_strlen(ft_strchr(str, '=')));
	}
	else
		par.len = 0;
	if (!valid_name("export", str, &par))
	{
		var_error(from, str, 0);
		return (1);
	}
	return (0);
}

int	allowed_char(char c, char *allowed)
{
	int	i;
	int	len;
	int	ind;

	i = 0;
	len = ft_strlen(allowed);
	ind = 0;
	while (i < len)
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
