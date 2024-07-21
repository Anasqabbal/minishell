/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/30 13:30:49 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/21 15:51:38 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

	/*4 functions*/

// t_list	*ft_getenv_ours(char *str, t_list *env)
// {
// 	char	*tmp;
// 	int		f_l;

// 	tmp = ft_strchr(str, '=');
// 	if (!tmp)
// 		return (NULL);
// 	f_l = ft_strlen(str) - ft_strlen(tmp) + 1;
// 	while (env)
// 	{
// 		if (!ft_strncmp(env->content, str, f_l))
// 			return (env);
// 		env = env->next;
// 	}
// 	return (NULL);
// }

t_list	*ft_getenv_ours(char *str, t_list *env)
{
	char	*tmp;
	int		j;

	while (env)
	{
		j = -1;
		tmp = env->content;
		while (tmp[++j] != '=' && tmp[j])
			;
		if (!ft_strncmp(env->content, str, j))
			return (env);
		env = env->next;
	}
	return (NULL);
}

t_list	*ft_getenv_ours_special(char *str, t_list *env)
{
	char	*tmp;
	int		j;

	while (env)
	{
		j = -1;
		tmp = env->content;
		while (tmp[++j] != '=' && tmp[j])
			;
		if (!ft_strncmp(env->content, str, ft_strlen(str)))
			return (env);
		env = env->next;
	}
	return (NULL);
}

static	t_list	*env_is_null(t_list **env, char **path)
{
	char	buffer[PATH_MAX];
	char	*res;

	if (getcwd(buffer, sizeof(buffer)) == NULL)
		perror("getcwd error");
	res = ft_strjoin("PWD=", buffer);
	if (!res)
		return (NULL);
	ft_lstadd_back(env, ft_lstnew(res));
	ft_lstadd_back(env, ft_lstnew(ft_strdup("SHLVL=1")));
	*path = "PATH=/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.";
	return (*env);
}

char	*nw_vl(t_list *env, int ii, char *s, char *s1)
{
	int		i;
	int		res;
	char	*re;

	i = -1;
	res = 0;
	env = ft_getenv_ours("SHLVL=", env);
	if (!env)
		return (ft_strdup("SHLVL=1"));
	s = env->content;
	while (s && s[++i])
	{
		if (ft_isdigit(s[i]))
			break ;
	}
	while (s[i] >= '0' && s[i] <= '9')
		res = res * 10 + (s[i++] - 48);
	if (res < 999)
	s1 = ft_itoa(res + ii);
	if (!s1 && res < 999)
		return (NULL);
	re = my_strjoin("SHLVL=", s1);
	if (!re)
		return (free (s1), printf ("khrjt mn hna\n"), NULL);
	return (free(s1), re);
}

t_list	*ft_envdup(char **env, char **path)
{
	int		i;
	t_list	*res;
	t_list	*head;
	char	*shlvl;

	i = -1;
	head = NULL;
	*path = NULL;
	if (!env[0])
		return (env_is_null(&head, path), head);
	while (env[++i])
	{
		if (ft_strnstr(env[i], "OLDPWD=", 8))
			continue ;
		res = ft_lstnew(ft_strdup(env[i]));
		if (!res)
			return (ft_lstclear(&head, free), NULL);
		ft_lstadd_back(&head, res);
	}
	shlvl = nw_vl(head, 1, NULL, NULL);
	if (!shlvl)
		return (ft_lstclear(&head, free), NULL);
	export1(shlvl, &head);
	export1("OLDPWD", &head);
	return (free(shlvl), head);
}
