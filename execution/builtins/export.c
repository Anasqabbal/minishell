/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:04:18 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/09 09:28:54 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_print_lst(t_list *envp, int indice)
{
	char	*str;
	int		i;

	if (indice == 0)
	{
		while (envp)
		{
			str = envp->content;
			if (ft_strchr(str, '='))
			{
				i = -1;
				ft_printf("declare -x ");
				while (str[++i] != '=')
					ft_printf("%c", str[i]);
				ft_printf("%c\"%s\"\n", str[i], (str + i + 1));
			}
			else
				ft_printf("declare -x %s\n", envp->content);
			envp = envp->next;
		}
	}
}

static int	valide_par(char *from, char *str)
{
	t_par	par;

	par.first = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_";
	par.mid = "abcdefghijklmnopqrstuvwxyz\
		ABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789=";
	par.last = "abcdefghijklmnopqrstuvwxyz\
		ABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789=+";
	if (str)
	{
		if (!ft_strchr(str, '='))
			par.len = ft_strlen(str);
		else
			par.len = ft_strlen(str) - (ft_strlen(ft_strchr(str, '=')));
	}
	else
		par.len = 0;
	if (!valid_name("export", str, &par))
	{
		var_error(from, str, 0);
		return (1);
	}
	return (0);
}

void	*add_to_env(char	*str, t_list	**envp)
{
	t_list	*new;
	t_list	*env;

	env = *envp;
	new = ft_lstnew(ft_strdup(str));
	if (!new)
		return (NULL);
	ft_lstadd_back(&env, new);
	return (*envp);
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
	new = ft_getenv_ours(str, *env);
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

	new = ft_getenv_ours(str, *env);
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
	if (!opts[0])
		return (ft_print_lst(*envp, 0), 0);
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
