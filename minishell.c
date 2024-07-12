/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/12 17:00:37 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_clear_exec(t_exec **e)
{
	t_exec	*tmp;

	while (*e)
	{
		(*e)->in = to_free_f((*e)->in, (*e)->in_l);
		(*e)->out = to_free_f((*e)->out, (*e)->out_l);
		(*e)->cmd = to_free((*e)->cmd);
		free((*e)->path);
		(*e)->path = NULL;
		(*e)->env = to_free((*e)->env);
		(*e)->in_l = 0;
		(*e)->out_l = 0;
		(*e)->here_doc = to_free((*e)->here_doc);
		(*e)->size = 0;
		tmp = *e;
		*e = (*e)->n;
		free(tmp);
	}
	*e = NULL;
}
void print_lst(t_list *e)
{
	if (e)
	{
		while(e)
		{
			printf("lst>>>%s\n", e->content);
			e = e->next;
		}
	}
}

void	clear_prs(t_prs **c)
{
	t_prs	*tmp;

	while (*c)
	{
		if ((*c)->cmd)
		{
			free((*c)->cmd);
			(*c)->cmd = NULL;
		}
		if ((*c)->arg)
			(*c)->arg = to_free((*c)->arg);
		if ((*c)->opts)
			(*c)->opts = to_free((*c)->opts);
		if ((*c)->red)
			(*c)->red = to_free((*c)->red);
		tmp = *c;
		*c = (*c)->next;
		free(tmp);
	}
}

void	ft_print_prs(t_prs *c)
{
	if (c->cmd)
		ft_printf("   cmd == %s  \n", c->cmd);
	if (c->opts)
	{
		ft_printf("|   ___opts___   |\n");
		ft_printf("   opts == ");
		ft_2dprint(c->opts);
	}
	if (c->arg)
	{
		ft_printf("|    ___args___   |\n");
		ft_printf("   args == ");
		ft_2dprint(c->arg);
	}
	if (c->red)
	{
		ft_printf("|    ___red___   |\n");
		int i = 0;
		while(c->red[i])
		{
			if (!ft_strncmp(c->red[i], "<", 1))
			{
				ft_printf("    the infile ");
				ft_printf("%s\n    and its name %s\n", c->red[i], c->red[i + 1]);
			}
			else if (!ft_strncmp(c->red[i], ">", 1))
				{
				ft_printf("    the outfile ");
				ft_printf("  %s\n    and its name %s\n", c->red[i], c->red[i + 1]);
			}
			i += 2;
		}
	}
}
void	print_prs(t_prs *p)
{
	int i = 0;
	while (p)
	{
		printf("|-------%d-------|\n", i);
		ft_print_prs(p);
		p = p->next;
		i++;
	}
	printf("\n\n\n\n");
}

t_prs	*new_prs(char *cmd, char **opts, char **args)
{
	t_prs	*new;

	new = malloc(sizeof(t_prs));
	if (!new)
		return (NULL);
	new->cmd = cmd;
	new->arg = args;
	new->opts = opts;
	new->red = NULL;
	new->ex_code = 0;
	return (new);
}

t_prs	*set_values(int indice)
{
	t_prs	*h;

	(void) indice;
	h = malloc(sizeof(t_prs));
	if (!h)
		return(NULL);
	h->cmd = ft_strdup("ls");
	h->arg = NULL;
	h->opts = NULL;
	h->red = NULL;
	h->next = NULL;
	h->ex_code = 0;
	return (h);
}

void f(void){system("leaks minishell");}

int main(int ac, char **av, char **env)
{
	char	*input;
	char	*path;
	int		ret;
	t_prs	*n ;
	t_list	*envp;

	// envp = NULL;
	// atexit(f);
	envp = ft_envdup(env, &path);
	if (!envp || ac == -1 || !av)
		return (1);// malloc failed;
	n = NULL;
	ret = 0;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			break ;
		if (input && input[0] != '\0')
		{
			if (check_syntax(input, envp, &n, &ret))
			{
				print_prs(n);
				ret = start_exec(&n, &envp , ret, &path);
				if (input[0] != '\0')
					add_history(input);
			}
			clear_prs(&n);
			free(input);
		}
	}
	return (ft_lstclear(&envp, free), clear_prs(&n), ret);

	/* set a new variable in your struct to trakc the len of your here_doc to make the last one as input e->in_h_l */
}
