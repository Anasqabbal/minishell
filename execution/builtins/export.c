/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:04:18 by anqabbal          #+#    #+#             */
/*   Updated: 2024/06/29 12:57:41 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	ft_print_lst(t_list *envp, int indice)
{
	char *str;
	int	i;

	if (indice == 0)
	{
		while(envp)
		{
			if (ft_strncmp(envp->content, "_=", 2))
			{
				ft_printf("declare -x ");
				printf("%s\n", envp->content);
			}
			envp = envp->next;
		}
	}
	else if (indice == 1)
	{
		while(envp)
		{
			i = -1;
			str = envp->content;
			while(str[++i] != '=')
				ft_printf("%c", str[i]);
			envp = envp->next;
		}
	}
}

static	int	valide_par(char *from, char *str)
{
	t_par par;
	
	par.first = "+abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_ "; // allowed characters
	par.mid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789= /";
	par.last = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789= /";
	if (str)
		par.len = ft_strlen(str);
	else
		par.len = 0;

	if (!valid_name("export", str, &par))
	{
		var_error(from, str, 0);
		return (1);
	}
	return (0);
}

 void	*add_to_env(char *str, t_list **envp)
{
	t_list *new;
	t_list *env;

	env = *envp;
	new = ft_lstnew(ft_strdup(str));
	if (!new)
		return (NULL);
	ft_lstadd_back(&env, new);
	return (*envp);
}

static void	*edit_env(char *str, t_list **env, t_list *old)
{
	t_list *new;

	if (!env)
		return (NULL);
	new = ft_lstnew(ft_strdup(str));
	if (!new)
		return (NULL);
	if (!ft_lstremplace(env, old, new))
		return (ft_lstdelone(new, free), NULL);
	return (new);
}

void	*export1(char *str, t_list **env)
{
	t_list *new;
	t_list *tmp;

	if (ft_strchr(str, '='))
	{
		new = ft_getenv_ours(str, *env);
		if (!new)
			return (add_to_env(str, env));
		else
		{
			tmp = edit_env(str, env, new);
			if (!tmp)
				return (ft_lstdelone(new, free), NULL);
			return (tmp);
		}
	}
	return (str);
}

int	ft_export(char **opts, t_list **envp)
{
	int	i;
	int	ret;
	int ind;

	i = -1;
	ind = 0;
	ret = 0;
	if (!opts[0])
		return (ft_print_lst(*envp, 0), 0);
	else
	{
		while (opts[++i])
		{
			if (i == 0 && ft_strlen(opts[i]) == 1 && opts[i][0] == '+' && !opts[i + 1])
				ft_print_lst(*envp, 1);
			ret = valide_par("export", opts[i]);
			if (ret && i++ && ind++)
				continue ;
			else if (!export1(opts[i], envp))
				return(1);
		}
	}
	if (ind)
		return (1);
	return (ret);
}
