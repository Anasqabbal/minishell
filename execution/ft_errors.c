/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/29 08:33:00 by anqabbal         ###   ########.fr       */
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
	return (indice);
}

int	ft_error_files(int indice, int ret, char *n)
{
	ft__putstr_fd("minishell: ", 2);
	ft__putstr_fd(n, 2);
	if (indice == 13)
		ft_putendl_fd(": Permission denied", 2);
	else if (indice == 2)
		ft_putendl_fd(": No such file or directory", 2);
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
