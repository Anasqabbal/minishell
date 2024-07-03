/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_qts.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:30:26 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/29 08:31:26 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void	check_qts_h1(char *input, int *count, int *x)
{
	if(input[*x] == '|' || input[*x] == '>' || input[*x] == '<')
    	{
        	if ((input[*x] == '>' && input[*x + 1] == '>') || (input[*x] == '<' && input[*x + 1] == '<'))
        	{
        		(*x)++;
        		(*x)++;
       		}
        	(*count)++;
   	 	}
}

static void	check_qts_h(char *input, int *count, int *qts)
{
	int x;
	char hold;

	x = 0;
	while ((size_t)x < ft_strlen(input))
	{
		if (input[x] == '"' || input[x] == '\'')
		{
			(*qts)++;
			hold = input[x++];
			if (input[x] == '\0')
				break ;
			while ((size_t)x < ft_strlen(input))
			{
				if (input[x] == hold)
				{
					(*qts)++;
					break ;
				}
				x++;
			}
		}
		x++;
		check_qts_h1(input, count, &x);
	}
}

int check_qts(char *input, int *count, int *qts)
{
	check_qts_h(input, count, qts);
	if ((*qts) % 2 != 0)
		return(0);
	return (1);
}