/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/29 16:31:10 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_error_p(char *from, int indice)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(from, 2);
	if (indice == 127)
		ft_putstr_fd(": No such file or directory\n", 2);
	if (indice == 126)
		ft_putstr_fd(": Permission denied\n", 2);
	else if (indice / 2 == 126)
	{
		ft_putstr_fd(": is a directory\n", 2);
		return (indice / 2);
	}
	else if (indice == 2)
	{
		ft_putstr_fd(": filename argument required\n", 2);
		return (indice);
	}
	return (indice);
}

int	ft_ex_error(char *from, char *nam, int rt)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(from, 2);
	if (rt == 255)
	{
		ft_putstr_fd(nam, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (rt == 1)
		ft_putendl_fd("too many arguments", 2);
	return (rt);
}

int	ft_error_files(int indice, int ret, char *n)
{
	ft__putstr_fd("minishell: ", 2);
	ft__putstr_fd(n, 2);
	if (indice == 13)
		ft_putendl_fd(": Permission denied", 2);
	else if (indice == 2)
		ft_putendl_fd(": No such file or directory", 2);
	else if (indice == 255)
		ft_putendl_fd(": File name too long", 2);
	return (ret);
}

int	ft_error(char *from, int indice)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(from, 2);
	if (indice == 127)
		ft_putendl_fd(": command not found", 2);
	else if (indice == 126)
		ft_putendl_fd(": command is not excutable", 2);
	return (indice);
}
