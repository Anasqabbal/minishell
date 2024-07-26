/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:54:44 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/18 09:43:29 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*ft_envduppp(char **env)
{
	int i;
	t_list *res;
	t_list *head;

	i = 0;
	head = NULL;
	while (env[i])
	{
		res = ft_lstnew(ft_strdup(env[i]));
		if (!res)
			return (NULL);
		ft_lstadd_back(&head, res);
		i++;
	}
	return (head);	
}

void	ft_getenv_oursss(char *str, t_list *env, char *path)
{
	char	*tmp;
	int		f_l;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return ;
	f_l = ft_strlen(str) - ft_strlen(tmp) + 1;
	while (env)
	{
		if (!ft_strncmp(env->content, str, f_l))
		{
			free(env->content);
			env->content = ft_strdup(path);
		}
		env = env->next;
	}
}

t_list	*ft_getenv(char *str, t_list *env)
{
	char	*tmp;
	int		f_l;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (NULL);
	f_l = ft_strlen(str) - ft_strlen(tmp) + 1;
	while (env)
	{
		if (!ft_strncmp(env->content, str, f_l))
			return (env);
		env = env->next;
	}
	return (NULL);
}