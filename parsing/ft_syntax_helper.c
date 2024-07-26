/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax_helper.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:18:39 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/18 09:41:38 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int 	ft_syntax_h2(char *str, int x)
{
	if(!error_msg1(str, x))
		return(0);
	return (1);
}

static int ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}

static void	replacewihte_s_h(char *str, int *len, int *is_space)
{
	if (!(*is_space))
	{
		str[*len] = ' ';
		(*len)++;
		*is_space = 1;
	}
}

void replacewihte_s(char *str)
{
	int x;
	int len;
	int is_space;

	x = 0;
	is_space = 0;
	len = 0;
	while (str[x] != '\0')
	{
		if (ft_isspace(str[x]))
			replacewihte_s_h(str, &len, &is_space);
		else
		{
			str[len] = str[x];
			len++;
			is_space = 0;
		}
		x++;
	}
	str[len] = '\0';
}
