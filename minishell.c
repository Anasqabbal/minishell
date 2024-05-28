/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 by zgtaib            #+#    #+#             */
/*   Updated: 2024/05/28 16:30:53 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	clear_prs(t_prs *c)
{
	while(c)
	{
		if (c->cmd)
		{
			free(c->cmd);
			c->cmd = NULL;
		}
		if (c->arg)
			c->arg = to_free(c->arg);
		if (c->opts)
			c->opts = to_free(c->opts);
		if (c->in_f)
			c->in_f = to_free(c->in_f);
		if (c->in)
			c->in =  to_free(c->in);
		if (c->out_f)
			c->out_f = to_free(c->out_f);
		if (c->out)
			c->out = to_free(c->out);
		c = c->next;
	}
}

void	ft_printf_prs(t_prs *c)
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
	if (c->in && c->in_f)
	{
		ft_printf("|    ___in_f___   |\n");
		int i = 0;
		while(c->in[i] || c->in_f[i])
		{
			ft_printf("    the infile ");
			ft_printf("%s\n    and its name %s\n", c->in[i], c->in_f[i]);
			i++;
		}
	}
	if (c->out_f)
		ft_printf("your out_f is not NULL\n");
	if (c->out)
		ft_printf("your out is not NULL\n");
}
void	print_prs(t_prs *p)
{
	int i = 0;
	while (p)
	{
		printf("|-------%d-------|\n", i);
		ft_printf_prs(p);
		p = p->next;
		i++;
	}
	printf("\n\n\n\n");
}

t_prs *new_prs(char *cmd, char **opts, char **args)
{
	t_prs *new;

	new = malloc(sizeof(t_prs));
	if (!new)
		return(NULL);
	new->cmd = cmd;
	new->arg = args;
	new->opts = opts;
	new->in = NULL;
	new->in_f = NULL;
	new->out = NULL;
	new->out_f = NULL;
	new->next = NULL;
	new->ex_code = 0;
	return (new);
}

t_prs *set_values(int indice)
{
	char *cmd1;
	char **opts1;
	char **args1;
	t_prs *p, *p1, *p2;
	t_prs *head;

	p = NULL;
	ft_printf("your indice == %d\n", indice);
	if (indice <= 4)
	{
		cmd1 = ft_strdup("./test.c");
		opts1 = NULL;
		// opts1[0] = NULL;
		// opts1[1] = NULL;
		args1 = NULL;
		p = new_prs(cmd1, opts1, args1);
		if (!p)
		{
			ft_printf("return with NULL\n");
			return (NULL);
		}
		// p->in = malloc(sizeof(char *) * 2);
		// p->in[0] = ft_strdup("<");
		// p->in[1] = NULL;

		// p->in_f = malloc(sizeof(char *) * 2);
		// p->in_f[0] = ft_strdup("sdfs");
		// p->in_f[1] = NULL;
		indice--;
	}
	head = p;
	if (indice <= 3 && indice)
	{
		char *cmd2 = ft_strdup("./infile");
		char **opts2 = NULL;
		char **args2 = NULL;
		// malloc(sizeof(char *) * 2);
		// args2[0] = ft_strdup("test");
		// args2[1] = NULL;
		p->next = new_prs(cmd2, opts2, args2);
		indice--;
	}
	if (indice <= 2 && indice)
	{	
		char *cmd3 = ft_strdup("grep");
		if (!cmd3)
			return (printf("fialed cmd3\n"), NULL);
		//ft_printf("your cmd3 = %s\n", cmd3);
		char **opts3 = NULL;
		char **args3 = malloc(sizeof(char *) * 2);
		args3[0] = ft_strdup("simple");
		args3[1] = NULL;
		p1 = new_prs(cmd3, opts3, args3);
		if (!p1)
			return (printf("your p1 === NULLL"), NULL);
		p->next->next = p1;
		indice--;
	}
	if (indice == 1 && indice)
	{
		char *cmd4 = ft_strdup("grep");
		if (!cmd4)
			return (printf("fialed cmd4\n"), NULL);
		//ft_printf("your cmd4 = %s\n", cmd4);
		char **opts4 = NULL;
		char **args4 = malloc(sizeof(char *) * 2);
		args4[0] = ft_strdup("test2");
		args4[1] = NULL;
		p2 = new_prs(cmd4, opts4, args4);
		if (!p2)
			return (printf("your p1 === NULLL"), NULL);
		p->next->next->next = p2;
	}
	return (head);
}


int main(int ac, char **av, char **env)
{
	char	*input;
	t_prs	*n = NULL;
	t_list	*envp;

	envp = ft_envdup(env);
	if (!envp || ac == -1 || !av)
		return (1);// malloc failed;
	n = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input)
			return (free(input), ft_printf("\nexit\n"), 0);
		if (input && input[0] != '\0')
		{
			if (!check_syntax(input, envp, &n))
				write(2, "syntax error\n", 13);
			print_prs(n);
			 n->ex_code = start_exec(n, envp);
			if (input[0] != '\0')
				add_history(input);
		}
		printf("your exit code == %d\n", n->ex_code);
		clear_prs(n);
		free(input);
	}
}
