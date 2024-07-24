/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:04:18 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/24 14:41:32 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*add_to_env(char	*str, t_list	**envp)
{
	t_list	*new;
	t_list	*env;
	char	*res;

	env = *envp;
	res = NULL;
	if (ft_strchr(str, '+'))
		res = remove_plus(str, res);
	if (res)
		str = res;
	new = ft_lstnew(ft_strdup(str));
	if (!new)
		return (free(res), NULL);
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
	new = ex_getenv_ours(str, *env);
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

	new = ex_getenv_ours(str, *env);
	if (!new)
		return (add_to_env(str, env));
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
				return (1);
		}
	}
	if (ind)
		return (1);
	return (ret);
}
