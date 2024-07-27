/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:36:41 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/27 10:45:41 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*remove_plus(char *str, char *res)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * len);
	if (!(res))
		exit(1);
	while (str[i])
	{
		if (str[i] == '+')
		{
			i++;
			continue ;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

int	until_equ_sign(char *s, char c)
{
	int	i;

	i = 0;
	while (s[i] != c && s[i])
		i++;
	return (i);
}

t_list	*ex_getenv_ours(char *str, t_list *env, int j, char *tmp1)
{
	if (ft_strchr(str, '+'))
		tmp1 = remove_plus(str, tmp1);
	while (env)
	{
		j = -1;
		if (!tmp1)
		{
			while (str[++j] && str[j] != '=')
				;
			if (!ft_strncmp(env->content, str, j)
				&& until_equ_sign(env->content, '=') == j)
				return (env);
		}
		else if (tmp1)
		{
			while (tmp1[++j] && tmp1[j] != '=')
				;
			if (!ft_strncmp(env->content, tmp1, j))
				return (env);
		}
		env = env->next;
	}
	return (NULL);
}
