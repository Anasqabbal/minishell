/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:02:33 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/28 14:30:24 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static void delete_row(char ***array, int row_d)
{
	int rows;
	int x;
	
	rows = arg_count(*(array));
	x = row_d;
	free((*array)[row_d]);
	while (x < rows - 1)
	{
		(*array)[x] = (*array)[x + 1];
		x++;
	}
	(*array)[rows - 1] = NULL;
}

static void add_to_struct(char ***array, char *element)
{
	int count = 0;
	int i = 0;
    while (*array && (*array)[count])
        count++;
    char **new_array = (char **)malloc((count + 2) * sizeof(char *));
    while (i < count)
	{
        new_array[i] = (*array)[i];
		i++;
	}
    new_array[count] = ft_strdup(element);
    new_array[count + 1] = NULL;
    free(*array);
    *array = new_array;
}

static void parse_cmd(char **array, t_prs *node)
{
	int y;
	
	y = 1;
	if (array[0] == NULL|| array[0][0] == '\0')
		return ;
	node->cmd = array[0];
	while (array[y])
	{	
		if(array[y][0] == '-')
			add_to_struct(&node->opts, array[y]);
		else 
		{
			while(array[y])
			{
				add_to_struct(&node->arg, array[y]);
				y++;
			}
		}
		if (array[y])
			y++;
	}
}

void parse_red(char **array, t_prs *node)
{
	int x;
	
	x = 0;
	while (array[x])
	{
		if (array[x][0] == '>')
		{
			add_to_struct(&node->red, array[x]);
			delete_row(&array, x);
			if (array[x])
			{
				add_to_struct(&node->red, array[x]);
				delete_row(&array, x);
			}
			x = 0;
		}
		else if (array[x][0] == '<')
		{
			add_to_struct(&node->red, array[x]);
			delete_row(&array, x);
			if (array[x])
			{
				add_to_struct(&node->red, array[x]);
				delete_row(&array, x);
			}
			x = 0;
		}
		else 
			x++;
	}
	parse_cmd(array, node);
}
