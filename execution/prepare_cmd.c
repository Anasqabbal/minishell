/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:35:09 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/28 16:08:16 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **join_cmd_and_args(char *cmd, char **opts, int len)
{
	char	**res;
	int		i;
	int		len2;

	i = -1;
	res = ft_calloc(sizeof(char *), (len + 2));
	if (!res)
		return (NULL);//malloc failed;
	while (++i < len + 1)
	{
		if (i == 0)
			len2 = ft_strlen(cmd);
		else
			len2 = ft_strlen(opts[i - 1]);
		res[i] = malloc(sizeof(char) * (len2 + 1));
		if (!res[i])
			return(to_free(res), NULL); //malloc failed;
		if (i == 0)
			ft_memcpy(res[i], cmd, len2);
		else
			ft_memcpy(res[i], opts[i - 1], len2);
		res[i][len2] = '\0';
	}
	return (res);
}

static char *correct_it(char *s)
{
	int len;
	char *res;
	int		i;
	int 	j;

	i = -1;
	j = 1;
	len = ft_strlen(s) - 2;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while(++i < len)
		res[i] = s[j++];
	res[len] = '\0';
	return(res);
}

static void correct_args(char ***args)
{
	char	**cor;
	char	*tmp;
	int		i;

	i = 0;
	if (*args)
	{
		cor = ft_2dstrdup(*args);
		while(cor[i])
		{
			if (ft_strchr(cor[i], '\"'))
			{
				tmp = cor[i];
				cor[i] = correct_it(cor[i]);
				if (!cor[i])
				{
					cor[i] = tmp;
					return ;
				}
				free(tmp);
			}
			i++;
		}
		*args = cor;
	}
}

char **prepare_cmd(char *cmd, char **opts, char **args)
{
	char	**res;
	char	**res2;

	res = NULL;
	correct_args(&args);
	if (!cmd)
		return (NULL);
	if (opts || args)
	{
		res = ft_2dstrjoin(opts, args);
		if (!res)
			return (printf("prepare cmd, 1\n"), NULL);
	}
	res2 = join_cmd_and_args(cmd, res, calcul_args(res));
	if (!res2)
		return (to_free(res),printf("prepare cmd, 2\n"), NULL);
	to_free(res);
	to_free(args);
	return(res2);
}
