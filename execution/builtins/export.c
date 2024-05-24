/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 18:04:18 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/11 16:14:20 by anqabbal         ###   ########.fr       */
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
				printf("%s\n", envp->content);
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
	int		i;
	
	par.first = "+abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_ ";
	par.mid = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789= ";
	par.last = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ_01233456789= ";
	par.len = ft_strlen(str);

   	i = -1; 
	while(str[++i] != '=' && str[i]);
	if (str[i] && !ft_isalpha(str[i - 1]))
	{
		var_error(from, str, 0);
		return (0);
	}
	if (!valid_name("export", str, &par))
	{
		var_error(from, str, 0);
		return (0);
	}
	return (1);
}

static void	*add_to_env(char *str, t_list *env)
{
	int	last;
	int	i;
	t_list *prev;
	t_list *new;

	if (!env)
		return (NULL);
	new = ft_lstnew(ft_strdup(str));
	if (!new)
		return (NULL);
	i = -1;
	prev = NULL;
	last = ft_lstsize(env);
	while (++i < last - 1)
	{
		if (i == last - 2)
			prev = env;
		env = env->next;
	}
	if (prev)
		prev->next = new;
	new->next = env;
	return (env);
}

static void	*edit_env(char *str, t_list *env, t_list *old)
{
	t_list *new;

	if (!env)
		return (NULL);
	new = ft_lstnew(ft_strdup(str));
	if (!new)
		return (NULL);
	if (!ft_lstremplace(&env, old, new))
		return (ft_lstdelone(new, free), NULL);
	return (new);
}

void	*export1(char *str, t_list *env)
{
	t_list *new;
	t_list *tmp;
	
	if (ft_strchr(str, '='))
	{
		new = ft_getenv_ours(str, env);
		if (!new)
		{
			printf("add\n");
			return (add_to_env(str, env));
		}
		else
		{
			printf("edit\n");
			tmp = edit_env(str, env, new);
			if (!tmp)
				return (ft_lstdelone(new, free), NULL);
			return (tmp);
		}
	}
	return (str);
}

int	ft_export(char **opts, t_list *envp)
{
	int	i;

	i = 2;
	if (!opts)
	{
		ft_print_lst(envp, 0);
		return (0);
	}
	else
	{
		while (opts[i])
		{
			if (i == 0 && ft_strlen(opts[i]) == 1 && opts[i][0] == '+' && !opts[i + 1])
				ft_print_lst(envp, 1);
			if (!valide_par("export", opts[i]) || !export1(opts[i], envp))
			{
				return(0);
			}
			i++;
		}	
	}
	return (1);
}