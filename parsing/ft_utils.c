/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:36:31 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/27 20:39:07 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
		if (str[x])
			x++;
	}
}
void turn_double(char *str, int ndx)
{
	int x;
	char hold;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '"')
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
int turn_dollar(char *str, int y)
{
	int x;
	char hold;
	int ho;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '"' || str[x] == '\'')
        {
          	hold = str[x];
			ho = x;
            x++;
			if (str[x] == '\0')
				break ;
           	while (str[x] != '\0')
            {
				if (str[x] == hold)
				{
					if (str[y] == '$' && y > ho && y < x)
						return (1);
					break;
				}
                x++;
            }
		}
		x++;
	}
	return (0);
}
