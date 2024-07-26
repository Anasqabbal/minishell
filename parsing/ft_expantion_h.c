/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion_h.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:28:31 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/21 17:47:31 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static int handle_default_case(int var_len, int *x)
{
	int len;
	int y;

	len = 1;
	y = 0;
	(*x)++;
	while (y < var_len)
	{
		len++;
		y++;
	}
	*x += var_len;
	return (len);
}
static int handle_successful_expansion(char *expans, int var_len, int *x)
{
	int len;

	len = ft_strlen(expans);
	*x += (int)var_len + 1;
	return (len);
}
static int calaculate_expan_len_h(char *str, t_list *env, int *x)
{	
	int		var_len;
	int		ndx;
	int		len;
	char	*var;
	char	*expans;
	
	var = extract_virable(&str[*x], &var_len);
	ndx = 0;
	len = 0;
	expans = expand_variable(var, env, &ndx);
	free(var);
	if (expans)
		len += handle_successful_expansion(expans, var_len, x);
	else if(!expans && ndx == 0)
	{
		free(str);
		exit (1);
	}
	else
		len += handle_default_case(var_len, x);
	return (free(expans), len);
}
int calaculate_expan_len(char *str, t_list *env)
{
	int	len;
	int x;

	x = 0;
	len = 0;
	while ((size_t)x < ft_strlen(str))
	{
		if(str[x] == '$')
			len += calaculate_expan_len_h(str, env, &x);
		else
		{
			len++;
			x++;
		}
	}
	return (len);
}
void turn_here_do(char *str)
{
	int x;

	x = 0;
	while ((size_t)x < ft_strlen(str))
	{
		if(str[x] == '<' && str[x + 1] == '<')
		{
			x += 3;
			while (str[x] && str[x] != ' ')
			{
				if (str[x] == '$')
					str[x] *= -1;
				x++;
			}	
		}
		x++;
	}
}
