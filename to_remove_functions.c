#include "minishell.h"

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

void	ft_print_exec(t_exec *e)
{
	while (e)
	{
		printf("-----redirections----\n");
		if (!e->in)
			printf("your e->in is NULL\n");
		printf("the len of in_l == %d\n", e->in_l);
		if(!e->out)
			printf("your e->out is NULL\n");
		printf("the len of out_l == %d\n", e->out_l);
		printf("-----your command-------\n");
		if(e->cmd)
		{
			if (e->cmd[0])
				ft_2dprint(e->cmd);
			else
				printf("you command is NULL");
		}
		else
			printf("your command is NULL\n");
		printf("---------------your PATH--------\n");
		if (e->path)
			printf("your path == %s", e->path);
		printf("---------------your environment -----------------\n");
		if (e->env)
			ft_2dprint(e->env);
		printf("-----------------your here_doc---------------\n");
		if(e->here_doc && printf("---here_doc---\n"))
			ft_2dprint(e->here_doc);
		else
			printf("your here_doc is NULL\n");
		printf("the size == %d\n", e->size);

		printf("\n\n\n");
		e = e->n;
	}
	
}