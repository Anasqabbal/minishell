/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   additional_ft2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 16:40:14 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/04 11:22:52 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	calcul_strs(char *s1, char **s2)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s2 && s2[i])
	{
		if (!ft_strncmp(s2[i], s1, ft_strlen(s1)))
			count++;
		i++;
	}
	return (count);
}

void	*add_to_env(char	*str, t_list	**envp)
{
	t_list	*new;
	t_list	*env;
	char	*res;
	char	*str1;

	env = *envp;
	res = NULL;
	if (ft_strchr(str, '+'))
		res = remove_plus(str, res);
	if (res)
		str = res;
	str1 = ft_strdup(str);
	if (!str1)
		return (NULL);
	new = ft_lstnew(str1);
	if (!new)
		return (free(str1), free(res), NULL);
	ft_lstadd_back(&env, new);
	return (free(res), *envp);
}

int	initialize_t_all(t_prs *p, t_list **envp, t_exec *e, t_all *a)
{
	a->p = p;
	a->e = e;
	a->envp = envp;
	a->ret = 0;
	a->out = -1;
	a->indice = 0;
	a->i = 0;
	a->pi = 0;
	a->pr = 0;
	if (g_sig == 1)
		return (1);
	return (0);
}

int	ft_is_pipe(int fd, int ret)
{
	struct stat	st;

	if (fd == -1 || ret == -1)
		return (0);
	if (fstat(fd, &st) == -1)
		return (perror("fstat"), -1);
	if (S_ISFIFO(st.st_mode))
		return (1);
	else
		return (0);
}

int	ft_envdup_exept(t_list	*envp, char	*str, t_list	**new)
{
	t_list	*res;
	t_list	*head;
	int		j;
	char	*s;

	head = NULL;
	if (!envp)
		return (0);
	while (envp)
	{
		j = -1;
		s = envp->content;
		while (s[++j] && s[j] != '=')
			;
		if (!str || ft_strncmp(envp->content, str, j))
		{
			res = ft_lstnew(ft_strdup(envp->content));
			if (!res)
				return (ft_lstclear(&head, free), -1);
			ft_lstadd_back(&head, res);
		}
		envp = envp->next;
	}
	*new = head;
	return (0);
}
