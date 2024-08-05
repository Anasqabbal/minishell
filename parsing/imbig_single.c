/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   imbig_single.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 15:10:41 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/05 13:01:03 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	handle_spe(char *str, int *x)
{
	int	count;

	count = 0;
	turn_back(str, 1);
	while (1)
	{
		if (str[*x] == ' ' || !str[*x])
		{
			turn_back(str, 1);
			break ;
		}
		if (str[*x] * -1 == '$')
		{
			turn_back(str, 1);
			if (turn_dollar_2(str, *x))
				count++;
			turn_back(str, 1);
		}
		if (str[*x])
			(*x)++;
	}
	return (count);
}

static int	count_imbig_si(char *str)
{
	int	x;
	int	ndx;

	x = 0;
	ndx = 0;
	while (str[x])
	{
		if (str[x] == '>' || (str[x] == '<' && str[x + 1] != '<'))
		{
			if (str[x] == '>' && str[x + 1] == '>')
				x += 3;
			else if (str[x] == '>' || str[x] == '<')
				x += 2;
			if (handle_spe(str, &x) != 0)
				ndx++;
		}
		if (str[x])
			x++;
	}
	return (ndx);
}

static int	handle_spe_ndx(char *str, int *hold, int *grip)
{
	int	count;

	count = 0;
	if (str[*hold] == '>' && str[*hold + 1] == '>')
	{
		*grip = *hold + 1;
		*hold += 3;
	}
	else if (str[*hold] == '>' || str[*hold] == '<')
	{
		*grip = *hold;
		*hold += 2;
	}
	turn_back(str, 1);
	count = handle_loop_ndx(str, hold);
	return (count);
}

static int	return_ndx(char *str, int x)
{
	int	hold;
	int	grip;
	int	count;

	hold = x;
	while (str[hold])
	{
		if ((str[hold] == '>' || (str[hold] == '<' && str[hold + 1] != '<'))
			&& !turn_dollar_here(str, hold))
		{
			count = handle_spe_ndx(str, &hold, &grip);
			if (count != 0)
				return (grip);
		}
		if (str[hold])
			hold++;
	}
	return (-1);
}

char	*imbig_sing(char *str, t_list *env)
{
	int		x;
	char	*cmd;
	int		y;

	x = 0;
	y = 0;
	cmd = malloc((ft_strlen(str) + count_imbig_si(str) + 1) * sizeof(char));
	if (!cmd)
	{
		ft_lstclear(&env, free);
		free(str);
		exit(1);
	}
	while (str[x])
	{
		if (str[x] && str[x] == '<' && str[x + 1] == '<' && str[x + 2] == '<')
			the_three(str, cmd, &y, &x);
		if (x == return_ndx(str, x))
			retunr_ndx_cop(str, cmd, &y, &x);
		else
			cmd[y++] = str[x++];
	}
	cmd[y] = '\0';
	return (free(str), cmd);
}
