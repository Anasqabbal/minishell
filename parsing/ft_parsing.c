/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 16:02:33 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/30 19:30:38 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	delete_row(char ***array, int row_d)
{
	int	rows;
	int	x;

	rows = arg_count(*(array));
	x = row_d;
	while (x < rows - 1)
	{
		(*array)[x] = (*array)[x + 1];
		x++;
	}
	(*array)[rows - 1] = NULL;
}

static int	add_to_struct(char ***array, char *element)
{
	int		count;
	int		i;
	char	**new_array;

	count = 0;
	i = 0;
	while (*array && (*array)[count])
		count++;
	new_array = (char **)malloc((count + 2) * sizeof(char *));
	if (!new_array)
		return (-1);
	while (i < count)
	{
		new_array[i] = (*array)[i];
		i++;
	}
	new_array[count] = element;
	new_array[count + 1] = NULL;
	free(*array);
	*array = new_array;
	return (0);
}

static int	parse_cmd(char **array, t_prs *node)
{
	int	y;

	y = 1;
	if (array[0] == NULL)
		return (0);
	node->cmd = array[0];
	while (array[y])
	{
		if (array[y][0] == '-')
		{
			if (add_to_struct(&node->opts, array[y]) == -1)
				return (-1);
		}
		else
		{
			while (array[y])
			{
				if (add_to_struct(&node->opts, array[y++]) == -1)
					return (-1);
			}
		}
		if (array[y])
			y++;
	}
	return (0);
}

int	parse_red_helper(char **array, t_prs *node, int x, int ndx)
{
	if (ndx == 0)
	{
		if (add_to_struct(&node->red, array[x]) == -1)
			return (-1);
		delete_row(&array, x);
		if (array[x])
		{
			if (add_to_struct(&node->red, array[x]) == -1)
				return (-1);
			delete_row(&array, x);
		}
	}
	if (ndx == 1)
	{
		if (add_to_struct(&node->red, array[x]) == -1)
			return (-1);
		delete_row(&array, x);
		if (array[x])
		{
			if (add_to_struct(&node->red, array[x]) == -1)
				return (-1);
			delete_row(&array, x);
		}
	}
	return (0);
}

int	parse_red(char **array, t_prs *node)
{
	int	x;

	x = 0;
	while (array[x])
	{
		if (array[x][0] == '>')
		{
			if (parse_red_helper(array, node, x, 0) == -1)
				return (-1);
			x = 0;
		}
		else if (array[x][0] == '<')
		{
			if (parse_red_helper(array, node, x, 0) == -1)
				return (-1);
			x = 0;
		}
		else
			x++;
	}
	if (parse_cmd(array, node) == -1)
		return (-1);
	return (0);
}
