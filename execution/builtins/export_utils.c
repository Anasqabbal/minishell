/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/24 14:36:41 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/31 17:58:37 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	export_exit_code(t_list **env, t_exec *e)
{
	char	*itoa_res;
	char	*res;

	itoa_res = ft_itoa(e->ex);
	if (!itoa_res)
		return (-1);
	res = my_strjoin("_=", itoa_res);
	if (!res)
		return (free(itoa_res), -1);
	if (!export1(res, env))
		return (free(itoa_res), free(res), -1);
	return (free(itoa_res), free(res), 0);
}

int	export_with_equal(char *str, t_list **env)
{
	char	*res;
	char	*res1;
	char	*add;
	int		len;
	int		i;

	i = -1;
	len = ft_strlen(str) - ft_strlen(ft_strchr(str, '='));
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (-1);
	add = ft_strchr(str, '+');
	if (add && add < ft_strchr(str, '='))
		len -= 1;
	while (++i < len)
		res[i] = str[i];
	res[i] = '\0';
	res1 = my_strjoin("_=", res);
	if (!res1)
		return (free(res), -1);
	if (!export1(res1, env))
		return (free(res), free(res1), -1);
	return (free(res), free(res1), 0);
}

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
		return (NULL);
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
				return (free(tmp1), env);
		}
		else if (tmp1)
		{
			while (tmp1[++j] && tmp1[j] != '=')
				;
			if (!ft_strncmp(env->content, tmp1, j))
				return (free(tmp1), env);
		}
		env = env->next;
	}
	return (free(tmp1), NULL);
}
