/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:33:49 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/05 13:01:19 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	put_spaces_h(char *cmd, int *x, int *y, char *str)
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

static void	put_spaces_h1(char *cmd, int *x, int *y, char *str)
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
		return (free(cmd), NULL);
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

static void	help_pip_split(t_list *env, char *final, char **splt_pip, int ndx)
{
	if (ndx == 0)
	{
		ft_lstclear(&env, free);
		free(final);
		exit(1);
	}
	else if (ndx == 1)
	{
		free_it(splt_pip, arg_count(splt_pip));
		ft_lstclear(&env, free);
		free(final);
		exit(1);
	}
	else if (ndx == 2)
	{
		free(final);
		free_it(splt_pip, arg_count(splt_pip));
	}
}

t_prs	*pipe_split(char *cmd, int opp, t_list *env, int *red)
{
	char	**splt_pip;
	char	*final;
	t_prs	*head;
	t_prs	*curr;

	head = NULL;
	curr = NULL;
	final = put_spaces(cmd, opp);
	free_env(final, env);
	turn_back(final, 1);
	final = dollar_sign(final, 1);
	free_env(final, env);
	final = blurr_dollar_digit(final, 1);
	free_env(final, env);
	final = cmd_expa(final, env, red);
	final = imbig_sing(final, env);
	turn_back(final, 1);
	splt_pip = ft_split(final, '|');
	if (!splt_pip)
		help_pip_split(env, final, splt_pip, 0);
	if (pipe_split_h(splt_pip, &curr, &head, final) == -1)
		help_pip_split(env, final, splt_pip, 1);
	help_pip_split(env, final, splt_pip, 2);
	turning_it_back(head);
	return (head);
}
