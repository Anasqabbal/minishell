/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:04:18 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/27 12:53:35 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

/*5 functions */

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

void	*with_plus(char *str, t_list **env, t_list *old, t_list	*new)
{
	char	*n_s;
	int		i;
	int		j;

	i = -1;
	j = -1;
	while (str[++i] && str[i] != '=')
		;
	n_s = ft_calloc(sizeof(char), ft_strlen(str + i + 1) + 1);
	if (!n_s)
		return (NULL);
	if (ft_strchr(old->content, '='))
		i++ ;
	while (str[i])
		n_s[++j] = str[i++];
	new = ex_getenv_ours(str, *env, -1, NULL);
	if (!new)
		return (free(n_s), NULL);
	str = my_strjoin(new->content, n_s);
	if (!str)
		return (free(n_s), NULL);
	new = ft_lstnew(ft_strdup(str));
	if (!new)
		return (free(n_s), free(str), NULL);
	if (!ft_lstremplace(env, old, new))
		return (ft_lstdelone(new, free), free(str), free(n_s), NULL);
	return (free(str), free(n_s), new);
}

static void	*edit_env(char *str, t_list **env, t_list *old)
{
	t_list	*new;
	char	*add;

	if (!env)
		return (NULL);
	add = ft_strchr(str, '+');
	if (add && add < ft_strchr(str, '='))
		return (with_plus(str, env, old, NULL));
	else
	{
		new = ft_lstnew(ft_strdup(str));
		if (!new)
			return (NULL);
		if (!ft_lstremplace(env, old, new))
			return (ft_lstdelone(new, free), NULL);
		return (new);
	}
}

void	*export1(char	*str, t_list	**env)
{
	t_list	*new;
	t_list	*tmp;
	t_list	*res;

	new = ex_getenv_ours(str, *env, -1, NULL);
	if (!new)
	{
		res = add_to_env(str, env);
		if (!res)
			return (NULL);
		return (res);
	}
	else
	{
		if (ft_strchr(str, '='))
		{
			tmp = edit_env(str, env, new);
			if (!tmp)
				return (NULL);
		}
		return (str);
	}
	return (str);
}

int	ft_export(char **opts, t_list **envp)
{
	int	i;
	int	ret;
	int	ind;

	i = -1;
	ind = 0;
	ret = 0;
	if (it_is_with_options(opts, 0, "export"))
		return (2);
	if (!opts[0])
		return (ft_sort_ascii(*envp), 0);
	else
	{
		while (opts[++i])
		{
			ret = valide_par("export", opts[i]);
			if (ret && ++ind)
				continue ;
			else if (!export1(opts[i], envp))
				return (-1); /* my you need to free the all and exit here */
		}
	}
	if (ind)
		return (1);
	return (ret);
}