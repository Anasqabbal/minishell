/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:33:49 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/29 16:10:14 by anqabbal         ###   ########.fr       */
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

    str = (char *)malloc((ft_strlen(cmd) + (count * 2) + 2) * sizeof(char));
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
void turning_it_back(t_prs *head)
{
	t_prs *curr;
	int x;

	curr = head;
	while (curr != NULL)
	{
		x = 0;
		if (curr->cmd)
		{
			while (curr->cmd[x])
			{
				if (curr->cmd[x] < 0)
					curr->cmd[x] *= -1;
				x++;
			}
		}
		if (curr->arg)
			expo_turn(curr->arg);
		if (curr->red)
			expo_turn(curr->red);
		if (curr->opts)
			expo_turn(curr->opts);
		curr = curr->next;
	}
}
t_prs *pipe_split(char *cmd, int opp, t_list *env, int *red)
{	
	char **splt_pip;
	char *final;
	t_prs *head = NULL;
	t_prs *curr = NULL;

	final = put_spaces(cmd, opp);	
	turn_back(final, 1);
	// printf("1%s\n", final);
	final = dollar_sign(final, 1);
	// printf("2%s\n", final);
	final = blurr_dollar_digit(final, 1);
	// printf("**%s\n", final);	
	final = cmd_expa(final, env, red);
	// printf("***%s\n", final);
	// printf("*******************************************************\n");	
	turn_back(final, 1);
	splt_pip = ft_split(final, '|');
	if (!splt_pip)
	{
		free(final);
		exit(1);
	}
	pipe_split_h(splt_pip, &curr, &head, final);
	free(final);
	free_it(splt_pip, arg_count(splt_pip));
	turning_it_back(head);
	return (head);
}