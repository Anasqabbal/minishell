/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:51:26 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/29 08:31:45 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static char	*skip_unnecessary_quotes(char *str) 
{
    int sign = 0; 
    int length = ft_strlen(str);
    char *result = (char *)malloc(length + 1);  
    if (!result) {
        return NULL;
    }
    int x = 0;
    int y = 0;
	while (str[x]) 
    {
        ft_check_quotes(str[x], &sign);
        if ((sign == 1 && str[x] == '\'') || (sign == 2 && str[x] == '"')) {
            x++;
            continue;
        }
        if ((sign == 0 && (str[x] == '\'' || str[x] == '"'))) {
            x++;
            continue;
        }
        result[y++] = str[x++];
    }
    result[y] = '\0';  
    return result;
}

static char **take_qoutes_off(char **array)
{
	int len = arg_count(array);
	int y = 0;
	char *hold;

	while (array[y])
	{
		turn_back(array[y], 1);
		y++;
	}
	char **cmd = (char **)malloc((len + 1) * sizeof(char *));
	if (!cmd)
	{
		free_it(array, len);
		return (NULL);
	}
	y = 0;
	while (y < len)
	{
		hold = skip_unnecessary_quotes(array[y]);
		if (!hold)
		{
			free_it(array, len);
			free_it(cmd, len);
			return (NULL);
		}
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
			free_it_h(splt_pip, com, 0);
		splt_space = ft_split(splt_pip[y], ' ');
		if(!splt_space)
			free_it_h(splt_pip, com, 0);
		no_q = take_qoutes_off(splt_space);
		if (!no_q)
			free_it_h(splt_pip, com, 0);
		free_it(splt_space, arg_count(splt_space));
		parse_red(no_q, new);
		fill_cmd(curr, head, new);
		y++;	
	}
}
