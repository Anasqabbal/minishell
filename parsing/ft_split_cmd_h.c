/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:51:26 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/28 14:30:40 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	the_while(char *str, char *result)
{
	int		x;
    int		y;
	int		sign;

	sign = 0;
	x = 0;
	y = 0;
	while (str[x]) 
    {
        ft_check_quotes(str[x], &sign);
        if ((sign == 1 && str[x] == '\'') || (sign == 2 && str[x] == '"')) 
		{
            x++;
            continue;
        }
        if ((sign == 0 && (str[x] == '\'' || str[x] == '"'))) 
		{
            x++;
            continue;
        }
        result[y++] = str[x++];
    }
    result[y] = '\0';  
}
char	*skip_unnecessary_quotes(char *str)
{
    char	*result; 

    result = (char *)malloc(ft_strlen(str) + 1); 
	if (!result)
        return NULL;
	the_while(str, result);
    return result;
}
void expo_turn(char **str)
{
	int x;
	int y;

	y = 0;
	while (str[y])
	{
		x = 0;
		while (str[y][x])
		{
			if (str[y][x] < 0)
				str[y][x] *= -1;
			x++;
		}
		y++;
	}
}
static char **take_qoutes_off(char **array)
{
	int 	y;
	char	*hold;
	char 	**cmd;
	int		len;

	len = arg_count(array);
	cmd = (char **)malloc((len + 1) * sizeof(char *));
	if (!cmd)
		return (NULL);
	y = 0;
	while (y < len)
	{
		hold = skip_unnecessary_quotes(array[y]);
		if (!hold)
			return (free_it(cmd, len), NULL);
		cmd[y] = hold;
		y++;
	}
	cmd[len] = NULL;
	return (cmd);
}
static void fill_cmd(t_prs **curr, t_prs **head, t_prs *new)
{
	  if (*head == NULL) 
        	*head = new;
         else 
            (*curr)->next = new;
        *curr = new;
}

void	pipe_split_h(char **splt_pip, t_prs **curr, t_prs **head, char *com)
{
	int y;
	char **splt_space;
	char **no_q;
	t_prs *new;

	y = 0;
	while (splt_pip[y] != NULL)
	{
		new = init_prs();
		if (!new)
			free_it_h(splt_pip, com, head);
		splt_space = ft_split(splt_pip[y], ' ');
		if(!splt_space)
			free_it_h2(splt_pip, com, head, new);
		no_q = take_qoutes_off(splt_space);
		if (!no_q)
			free_it_h2(splt_pip, com, head, new);
		free_it(splt_space, arg_count(splt_space));
		// expo_turn(no_q);
		parse_red(no_q, new);
		// free_it(no_q, arg_count(no_q));
		fill_cmd(curr, head, new);
		y++;	
	}
}
