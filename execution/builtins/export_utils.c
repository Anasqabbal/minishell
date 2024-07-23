/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 09:45:26 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/23 11:27:49 by anqabbal         ###   ########.fr       */
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
	while(str[i])
	{
		if (str[i] == '+')
		{
			i++;
			continue;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

t_list *ex_getenv_ours(char *str, t_list *env)
{
	char	*tmp1;
	int		j;

	tmp1 = NULL;
	if (ft_strchr(str, '+'))
		tmp1 = remove_plus(str, tmp1);
	while (env)
	{
		j = -1;
		if (!tmp1)
		{
			while(str[++j] && str[j] != '=')
				;
			if (!ft_strncmp(env->content, str, j))
				return (env);
		}
		else if (tmp1)
		{
			while(tmp1[++j] && tmp1[j] != '=')
				;
			 if (!ft_strncmp(env->content, tmp1, j))
				return (env);
		}
		env = env->next;
	}
	return (NULL);
}
