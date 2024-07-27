/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/19 17:24:25 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/27 11:31:24 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*add_new_line(char **res)
{
	char	*tmp;

	tmp = my_strjoin(*res, "\n");
	if (!tmp)
		return (NULL);
	free(*res);
	return (*res = tmp);
}
