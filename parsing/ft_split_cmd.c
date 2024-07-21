/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:33:49 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/20 16:45:56 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void put_spaces_h(char *cmd, int *x, int *y, char *str)
{
	if (cmd[*x + 1] == '>' || cmd[*x + 1] == '<')
	{	
		if (*y > 0 && str[*y - 1] != ' ') 
            str[(*y)++] = ' ';
		str[(*y)++] = cmd[(*x)++];
		str[(*y)++] = cmd[*x];
		if (cmd[*x + 1] != ' ' && cmd[*x + 1] != '\0')
            str[(*y)++] = ' ';
	}
	else
	{
		if (*y > 0 && str[*y - 1] != ' ') 
            str[(*y)++] = ' ';
        str[(*y)++] = cmd[*x];
	    if (cmd[*x + 1] != ' ' && cmd[*x + 1] != '\0')
        	str[(*y)++] = ' ';
	}
}

static void put_spaces_h1(char *cmd, int *x, int *y, char *str)
{
	if (*y > 0 && str[*y - 1] != ' ') 
        str[(*y)++] = ' ';
	str[(*y)++] = cmd[*x];
	if (cmd[*x + 1] != ' ' && cmd[*x + 1] != '\0')
    	str[(*y)++] = ' ';
}

static char	*put_spaces(char *cmd, int count)
{
	int		x;
    char	*str;
	int		y; 

    str = (char *)malloc((ft_strlen(cmd) + (count * 2)+ 1) * sizeof(char));
    if (!str)
	{
		free(cmd);
		exit(1);
	}
	y = 0;
	x = 0;
    while (cmd[x] != '\0')
	{
		if (cmd[x] == '|')
			put_spaces_h1(cmd, &x, &y, str);
		else if (cmd[x] == '>' || cmd[x] == '<')
			put_spaces_h(cmd, &x, &y, str);
		else 
            str[y++] = cmd[x];
        x++;
    }
    str[y] = '\0';
    return (free(cmd), str);
}

t_prs *pipe_split(char *cmd, int opp, t_list *env, int *ret)
{	
	char **splt_pip;
	char *final;
	t_prs *head = NULL;
	t_prs *curr = NULL;

	final = put_spaces(cmd, opp);	
	turn_back(final, 1);
	final = dollar_sign(final);
	final = cmd_expa(final, env, ret);
	turn_back(final, 1);
	splt_pip = ft_split(final, '|');
	if (!splt_pip)
	{
		free(final);
		exit(1);
	} 
	// free(final);
	// exit(0);
	pipe_split_h(splt_pip, &curr, &head, final);
	free(final);
	free_it(splt_pip, arg_count(splt_pip));
	return (head);
}
