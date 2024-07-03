/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/04 15:54:11 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/30 11:17:51 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int ft_error2(char *from, char *str, int indice)
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

int	static valid_par(char *from, char *str)
{
	t_par	par;

	par.first = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	par.mid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789";
	par.last = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789";
	par.len = ft_strlen(str);
	if (!valid_name(from, str, &par))
		return (ft_error2(from, str ,1));
	return (0);
}
t_list	*ft_envdup_exept(t_list *envp, char *str)
{
	int i;
	t_list *res;
	t_list *head;

	i = 0;
	head = NULL;
	while (envp)
	{
		if (!str || ft_strncmp(envp->content, str, ft_strlen(str)))
		{
			res = ft_lstnew(ft_strdup(envp->content));
			if (!res)
				return (ft_lstclear(&head, free), NULL);
			ft_lstadd_back(&head, res);
		}
		envp = envp->next;
	}
	return (head);	
}

t_list	*unset1(char *str, t_list *envp, char **path)
{
	char	*tmp;
	int		pos;
	t_list 	*head;
	t_list	*env;

	env = envp;
	tmp = ft_strjoin(str, "=");
	if (!tmp)
		return (NULL);
	if (*path && !ft_strncmp(tmp, "PATH=", 5))
		return (*path = NULL ,ft_envdup_exept(env, NULL));
	pos = ft_lstget_pos(tmp, env);
	if (pos == -1)
		return(free(tmp), ft_envdup_exept(env, NULL));
	head = ft_envdup_exept(env, tmp);
	if (!head)
		return (free(str), free(tmp), NULL);
	free(tmp);
	return (head);
}

int	ft_unset(char **str, t_list **env, char **path)
{
	int		i;
	t_list *new;
	t_list *tmp;
	int		ret;

	i = 0;
	if (!str || !str[i])
		return (0);
	else
	{
		while (str[i])
		{
			ret = valid_par("unset", str[i]);
			if (ret)
				return (ret);// invalid variable
			new = unset1(str[i], *env, path);
			if (!new)
				return (1); // malloc failed
			tmp = *env;
			*env = new;
			ft_lstclear(&tmp, free);
			i++;
		}
	}
	return (0);
}
