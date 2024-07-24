/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:54:11 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/24 17:20:50 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_error2(char *from, char *str, int indice)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(from, 2);
	if (indice == 1)
	{
		ft_putstr_fd(": ", 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(": not a valid identifier", 2);
	}
	return (indice);
}

static int	valid_par(char *from, char *str)
{
	t_par	par;

	par.first = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	par.mid = "abcdefghijklmnopqrstuvwxyz\
	ABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789";
	par.last = "abcdefghijklmnopqrstuvwxyz\
	ABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789";
	par.len = ft_strlen(str);
	if (!valid_name(from, str, &par))
		return (ft_error2(from, str, 1));
	return (0);
}

int	ft_envdup_exept(t_list	*envp, char	*str, t_list	**new)
{
	t_list	*res;
	t_list	*head;
	int		j;
	char	*s;

	head = NULL;
	while (envp)
	{
		j = -1;
		s = envp->content;
		while(s[++j] && s[j] != '=')
			;
		if (!str || ft_strncmp(envp->content, str, j))
		{
			res = ft_lstnew(ft_strdup(envp->content));
			if (!res)
				return (ft_lstclear(&head, free), 1);
			ft_lstadd_back(&head, res);
		}
		envp = envp->next;
	}
	*new = head;
	return (0);
}

int	unset1(char *str, t_list **envp, char **path, t_list **new)
{
	int		pos;
	t_list	*head;
	t_list	*env;

	env = *envp;
	if (path && *path && (str && !ft_strncmp(str, "PATH", 5)))
	{
		if (ft_envdup_exept(env, NULL, &head))
			return (1);
		return (*path = NULL, *new = head, 0);
	}
	pos = ft_lstget_pos(str, env);
	if (pos == -1)
	{
		if (ft_envdup_exept(env, NULL, &head))
			return(1);
		return (*new = head, 0);
	}
	if (ft_envdup_exept(env, str, &head))
		return (1);
	return (*new = head, 0);
}

int	ft_unset(char **str, t_list **env, char **path)
{
	int		i;
	t_list	*new;
	int		ret;
	int		ind;

	i = 0;
	ind = 0;
	if (!str || !str[i])
		return (0);
	if (it_is_with_options(str, 0, 0))
		return (2);
	while (str[i])
	{
		ret = valid_par("unset", str[i]);
		if (ret && ++ind && i++)
			continue ;
		if (unset1(str[i], env, path, &new))
			return (1);
		ft_lstclear(env, free);
		*env = new;
		i++;
	}
	if (ind)
		return (1);
	return (0);
}
