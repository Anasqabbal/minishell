/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:35:09 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/16 16:45:19 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*5 functions*/

char	**join_cmd_and_args(char *cmd, char **opts, int len)
{
	char	**res;
	int		i;
	int		len2;

	i = -1;
	res = ft_calloc(sizeof(char *), (len + 2));
	if (!res)
		return (NULL);
	while (++i < len + 1)
	{
		if (i == 0)
			len2 = ft_strlen(cmd);
		else
			len2 = ft_strlen(opts[i - 1]);
		res[i] = malloc(sizeof(char) * (len2 + 1));
		if (!res[i])
			return (to_free(res), NULL);
		if (i == 0)
			ft_memcpy(res[i], cmd, len2);
		else
			ft_memcpy(res[i], opts[i - 1], len2);
		res[i][len2] = '\0';
	}
	return (res);
}

char	**prepare_cmd(char *cmd, char **opts, char **args)
{
	char	**res;
	char	**res2;

	res = NULL;
	if (!cmd)
		return (NULL);
	if (opts || args)
	{
		res = ft_2dstrjoin(opts, args);
		if (!res)
			return (NULL);
	}
	res2 = join_cmd_and_args(cmd, res, calcul_args(res));
	if (!res2)
		return (to_free(res), NULL);
	to_free(res);
	return (res2);
}
