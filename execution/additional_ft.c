/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_ft.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 13:04:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/27 18:09:43 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **to_free(char **s)
{
	int i;

	i = -1;
	while(s && s[++i])
	{
		free(s[i]);
	}
	free(s);
	return (NULL);
}

int	calcul_args(char **args)
{
	int	i;

	i = -1;
	if (!args)
		return (0);
	while(args[++i]);
	return (i);
}

char **ft_2dstrdup(char **s)
{
	int		len;
	int		len2;
	char	**res;
	int		i;

	len = calcul_args(s);
	if (!len)
		return (printf("in 2DSTRDUP, len"), NULL);
	res = malloc(sizeof(char *) * (len + 1));
	if (!res)
		return (NULL);
	i = 0;
	while(s[i])
	{
		len2 = ft_strlen(s[i]);
		res[i] = ft_calloc(sizeof(char), (len2 + 1));
		if (!res[i])
			return (to_free(res), NULL);
		ft_memcpy(res[i], s[i], len2);
		i++;
	}
	res[len] = NULL;
	return (res);
}

char **ft_2dstrcpy(char **dst, char **src, int f_len)
{
	int i;

	i = -1;
	if (!src || !dst)
		return (NULL);
	while (++i < f_len && src[i])
	{
		dst[i] = ft_strdup(src[i]);
		if (!dst[i])
			return (to_free(dst), NULL);
	}
	dst[f_len] = NULL;
	return (dst);
}

char **ft_2dstrjoin(char **s1, char **s2)
{
	int f_len;
	char **res;
	
	if (!s1 && !s2)
		return(NULL);
	else if (!s1)
		return(ft_2dstrdup(s2));
	else if (!s2)
		return (ft_2dstrdup(s1));
	f_len = calcul_args(s1) + calcul_args(s2) + 1;
	res = ft_calloc(sizeof(char *), (f_len + 1));
	if (!res)
		return (NULL);
	ft_2dstrcpy(res, s1,  calcul_args(s1));
	ft_2dstrcpy(res + calcul_args(s1), s2,  calcul_args(s2));
	return (res);
}

// void f(void){system("leaks a.out");}

// int main(int ac, char **av)
// {
// 	atexit(f);
// 	if (ac == 1)
// 		return(printf("enter valid arg\n"), 1);
// 	else
// 	{
// 		char **res;
// 		char **res1;
// 		char **f_res;

// 		res = malloc(sizeof(char *) * (3 + 1));
// 		if (!res)
// 			return (printf("malloc failed\n"));
		
// 		res1 = malloc(sizeof(char *) * (3 + 1));
// 		if (!res1)
// 			return (printf("malloc failed\n"));
// 		ft_2dstrcpy(res, av, 3);
// 		ft_2dstrcpy(res1, av + 3, 3);

// 		f_res = ft_2dstrjoin(res, res1);
// 		if (!f_res)
// 			return (printf("NULL\n"), 1);
		
// 		int i = 0;
// 		while(f_res[i])
// 		{
// 			printf("%s\n", f_res[i]);
// 			i++;
// 		}
// 		to_free(f_res);
// 		to_free(res);
// 		to_free(res1);
// 	}
