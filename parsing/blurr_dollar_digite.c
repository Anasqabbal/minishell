/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   blurr_dollar_digite.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 20:21:33 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/02 15:09:33 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	blurr_dollar_digit_wh1(char *str, char *cmd, int *x, int *y)
{
	the_three(str, cmd, y, x);
	turn_back(str, 1);
	while (str[*x] && str[*x] != ' ')
	{
		if (str[*x] < 0)
			cmd[(*y)++] = str[(*x)++] * -1;
		else
			cmd[(*y)++] = str[(*x)++];
	}
	turn_back(str, 1);
}

static void	blurr_dollar_digit_wh2(char *str, char *cmd, int *x, int *y)
{
	cmd[(*y)++] = str[(*x)++];
	cmd[(*y)++] = str[(*x)++];
	if (str[*x] == '$' && ft_isdigit(str[*x + 1]))
	{
		if ((str[*x + 2] == ' ' || str[*x + 2] == '\0'))
			cmd[(*y)++] = str[(*x)++];
		else if ((!turn_dollar_2(str, *x)))
			*x += 2;
	}
	else
		cmd[(*y)++] = str[(*x)++];
}

static void	blurr_dollar_digit_wh(char *str, char *cmd, int *y, int ndx)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] == '<' && str[x + 1] == '<' && ndx == 1)
			blurr_dollar_digit_wh1(str, cmd, &x, y);
		else if (str[x] && (str[x] == '>' || str[x] == '<') && ndx == 1)
			blurr_dollar_digit_wh2(str, cmd, &x, y);
		else if (str[x] == '$' && ft_isdigit(str[x + 1])
			&& !turn_dollar_2(str, x))
			x += 2;
		else
			cmd[(*y)++] = str[x++];
	}
}

char	*blurr_dollar_digit(char *str, int ndx)
{
	int		x;
	char	*cmd;
	int		y;

	x = 0;
	y = 0;
	cmd = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!cmd)
		return (free(cmd), NULL);
	blurr_dollar_digit_wh(str, cmd, &y, ndx);
	cmd[y] = '\0';
	return (free(str), cmd);
}
