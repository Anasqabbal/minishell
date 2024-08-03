/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_ex_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 21:40:56 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/02 19:56:25 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	count_ex(char *cmd)
{
	int	x;
	int	count;

	count = 0;
	x = 0;
	while (cmd[x])
	{
		if (cmd[x] == '$' && cmd[x + 1] == '?')
			count++;
		x++;
	}
	return (count);
}

static void	ex_code_expa_free(t_list *env, char *st, char *cmd, char *ex_code)
{
	ft_lstclear(&env, free);
	free(st);
	free(ex_code);
	free(cmd);
	exit(1);
}

static void	ex_code_expa_free_1(t_list *env, char *st, char *cmd)
{
	ft_lstclear(&env, free);
	free(st);
	free(cmd);
	exit(1);
}

static void	ex_code_while(char *str, char *cmd, char *ex_code, int *y)
{
	int	x;

	x = 0;
	while (cmd[x])
	{
		if (cmd[x] == '$' && cmd[x + 1] == '?' && ex_code_zero(cmd, x))
		{
			ft_strcpy(&str[*y], "0");
			*y += ft_strlen("0");
			x += 2;
		}
		else if (cmd[x] == '$' && cmd[x + 1] == '?')
		{
			ft_strcpy(&str[*y], ex_code);
			*y += ft_strlen(ex_code);
			x += 2;
		}
		else
			str[(*y)++] = cmd[x++];
	}
}

char	*expand_ex_code(char *cmd, int *red, t_list *env, char *st)
{
	int		y;
	char	*ex_code;
	char	*str;
	int		count;
	int		len;

	ex_code = ft_itoa((*red));
	if (!ex_code)
		ex_code_expa_free_1(env, st, cmd);
	count = count_ex(cmd);
	len = ft_strlen(cmd) - (count * 2) + (ft_strlen(ex_code) * count);
	str = (char *)malloc((len + 2) * sizeof(char));
	if (!str)
		ex_code_expa_free(env, st, cmd, ex_code);
	y = 0;
	ex_code_while(str, cmd, ex_code, &y);
	str[y] = '\0';
	return (free(ex_code), free(cmd), str);
}
