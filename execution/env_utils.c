/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:30:49 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/10 14:41:41 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	*ft_getenv_org(char *str, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
 		if (ft_strnstr(env[i], str, ft_strlen(env[i])))
			return (env[i]);
		i++;
	}
	return (NULL);
}

t_list	*ft_getenv_ours(char *str, t_list *env)
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

t_list	*ft_envdup(char **env)
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
			return (ft_lstclear(&head, free),NULL);
		ft_lstadd_back(&head, res);
		i++;
	}
	return (head);	
}