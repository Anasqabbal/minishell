/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:04:18 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/22 16:27:12 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


char	*remove_plus(char *str, char *res)
{
	int	len;
	int	i;
	int	j;

	i = 0;
	j = 0;
	len = ft_strlen(str);
	res = malloc(sizeof(char) * len);
	if (!(res))
		exit(1);
	while(str[i])
	{
		if (str[i] == '+')
		{
			i++;
			continue;
		}
		res[j] = str[i];
		i++;
		j++;
	}
	res[j] = '\0';
	return (res);
}

t_list *ex_getenv_ours(char *str, t_list *env)
{
	char	*tmp1;
	int		j;

	tmp1 = NULL;
	if (ft_strchr(str, '+'))
		tmp1 = remove_plus(str, tmp1);
	if (tmp1)
		printf("after remove + your content became === %s\n", tmp1);
	while (env)
	{
		j = -1;
		if (!tmp1)
		{
			while(str[++j] && str[j] != '=')
				;
			if (!ft_strncmp(env->content, str, j))
				return (env);
		}
		else if (tmp1)
		{
			while(tmp1[++j] && tmp1[j] != '=')
				;
			 if (!ft_strncmp(env->content, tmp1, j))
				return ( env);
		}
		env = env->next;
	}
	return (NULL);
}
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
	while (str[++i])
		n_s[++j] = str[i];
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

	printf("EDIT\n");
	if (!env)
		return (NULL);
	if (ft_strchr(str, '+'))
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
		return (printf("ADD\n"), add_to_env(str, env));
	else
	{
		if (ft_strchr(str, '='))
		{
			printf("dkhl lhna\n");
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
		return (1);
	if (!opts[0])
		return (ft_print_export(*envp, 0), 0);
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
