/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:36:31 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/29 08:32:07 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void free_it_h(char **splt_pip, char *com, int ndx)
{
	if (ndx == 0)
	{
		free(com);
		free_it(splt_pip, arg_count(splt_pip));
		exit(1);
	}
}

int    ft_check_quotes(char c, int *sign)
{
    if (c == '"' && *sign == 2)
        *sign = 0;
    else if (c == '\'' && *sign == 1)
        *sign = 0;
    else if (c == '"' && *sign == 0)
        *sign = 2;
    else if (c == '\'' && *sign == 0)
        *sign = 1;
    return (0);
}

int arg_count(char **str)
{
	int x;

	x = 0;
	while (str[x] != NULL)
		x++;
	return (x);
}

void turn_back(char *str, int ndx)
{
	int x;
	char hold;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '"' || str[x] == '\'')
        {
          	hold = str[x];
            x++;
			if (str[x] == '\0')
				break ;
           	while (str[x] != '\0')
            {
				if (str[x] == hold)
                    break ;
				if (ndx == 1)
					str[x] *= -1;
                x++;
            }
		}
		x++;
	}
}

void	free_it(char **arg, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
