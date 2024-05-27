/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_errors.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/13 15:12:51 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/27 15:01:29 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

int 	ft_error(char *from, int indice)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(from, 2);
	if (indice == 127)
		ft_putendl_fd(": command not found", 2);
	else if (indice == 126)
		ft_putendl_fd(": command is not excutable", 2);
	else if (indice == 1)
		ft_putendl_fd(": not a valid identifier", 2);
	return (indice);
}