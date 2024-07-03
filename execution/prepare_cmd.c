/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 09:35:09 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/28 16:53:31 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/*5 functions*/

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

// static void lenght_it(char *s, int i, int *len, char c)
// {
// 	while(s[++i])
// 	{
// 		if (s[i] == '\'' || s[i] == '\"')
// 		{
// 			if (i && s[i - 1] != c) // tokhalif 
// 				(*len)++;
// 		}
// 	}
// }

// static char *save_seconde_quotes(char *s)
// {
// 	int i;
// 	char *tmp;
// 	int j;
// 	int len;

// 	i = 0;
// 	j = 0;
// 	len = ft_strlen(s);
// 	tmp = malloc (sizeof(char) * len);
// 	if (!tmp)
// 		return (NULL);//malloc failed;
// 	while (s[i])
// 	{
// 		if (s[i] == '\"')
// 		{
// 			while(s[++i] != '\"' && s[i])
// 			{
// 				tmp[j] = s[i];
// 				j++;
// 			}
// 			i++;
// 		}
// 		else if (s[i] == '\'')
// 		{
// 			while(s[++i] != '\'' && s[i])
// 			{
// 				tmp[j] = s[i];
// 				j++;
// 			}
// 			i++;
// 		}
// 		else
// 		{
// 			tmp[j] = s[i];
// 			j++;
// 			i++;
// 		}
// 	}
// 	while(j <= len)
// 		tmp[j++] = '\0';
// 	return (tmp);
// }


// static char *correct_it(char *s, int i, int j, int len)
// {
// 	char *res;

// 	if (ft_strchr(s, '\'') && ft_strchr(s, '\"'))
// 		return (save_seconde_quotes(s));
// 	lenght_it(s, i, &len, '\\');
// 	len = ft_strlen(s) - len;
// 	res = malloc(sizeof(char) * (len + 1));
// 	if (!res)
// 		return (NULL);
// 	i = -1;
// 	while(s[++i])
// 	{
// 		if (((s[i] == '\'' || s[i] == '\"') && ((i && s[i - 1] == '\\'))))
// 		{
// 			if (s[i] != '\\')
// 				res[++j] = s[i];
// 		}
// 		else if ((s[i] != '\'' && s[i] != '\"' && s[i] != '\\'))
// 			res[++j] = s[i];
// 	}
// 	while(++j <= len)
// 		res[j] = '\0';
// 	return(res);
// }

// static void correct_args(char ***args)
// {
// 	char	**cor;
// 	char	*tmp;
// 	int		i;

// 	i = 0;
// 	if (*args)
// 	{
// 		cor = ft_2dstrdup(*args);
// 		while(cor[i])
// 		{
// 			// if (ft_strchr(cor[i], '\"') || ft_strchr(cor[i], '\''))
// 			// {
// 			// 	tmp = cor[i];
// 			// 	cor[i] = correct_it(cor[i], -1, -1, 0);
// 			// 	if (!cor[i])
// 			// 	{
// 			// 		cor[i] = tmp;
// 			// 		return ;
// 			// 	}
// 			// 	free(tmp);
// 			// }
// 			i++;
// 		}
// 		*args = cor;
// 	}
// }

char **prepare_cmd(char *cmd, char **opts, char **args)
{
	char	**res;
	char	**res2;

	res = NULL;
	// correct_args(&args);
	// correct_args(&opts);
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
	// to_free(args);
	return(res2);
}



/*OLD CORRECT IT*/
// static char *correct_it(char *s, int i, int j, int len)
// {
// 	char *res;

// 	lenght_it(s, i, &len);
// 	len = ft_strlen(s) - len;
// 	res = malloc(sizeof(char) * (len + 1));
// 	if (!res)
// 		return (NULL);
// 	i = -1;
// 	while(s[++i])
// 	{
// 		if (((s[i] == '\'' || s[i] == '\"') && (i && !which_one(s[i - 1]))))
// 		{
// 			if (s[i] != '\\')
// 				res[++j] = s[i];
// 		}
// 		else if ((s[i] != '\'' && s[i] != '\"' && s[i] != '\\'))
// 			res[++j] = s[i];
// 	}
// 	while(++j <= len)
// 		res[j] = '\0';
// 	return(printf("your res == %s\n", res), res);
// }





/*
	1) check if the first char is one of the three characters ' " \
	2) and build your code about the next, instead the previouse to define what you need to do


*/