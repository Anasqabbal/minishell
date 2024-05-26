/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 by zgtaib            #+#    #+#             */
/*   Updated: 2024/05/26 18:22:04 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void to_free2(char **av)
{
	int i = -1;
	while (++i)
		free(av[i]);
	free(av);
}

static int m_strlen(char *str, char c)
{
	int i = -1;
	while(str[++i] && str[i] != c);
	return(i);
}

// void	set_values(t_prs *n, char *input)
// {
// 	m_strlen(input, 'c');
// 	char **av;
// 	// int j;
	
// 	av = ft_split(input, ' ');
// 	if (!av)
// 	{
// 		printf("split failed\n");
// 		return ;
// 	}
// 	n->opts = NULL;
// 	n->arg = NULL;

// 	//check the first arg

// 	if (ft_strncmp(av[0], ">", ft_strlen(av[0])) && ft_strncmp(av[0], "<", ft_strlen(av[0])) && ft_strncmp(av[0], ">>", ft_strlen(av[0])))
// 	{
// 		n->cmd = ft_strdup(av[0]);
// 		if (!n->cmd)
// 			printf("no commad\n");
// 		n->outfile = NULL;
// 		n->infile = NULL;
// 		if (split_strlen(input, ' ', 0) <= 3  && split_strlen(input, ' ', 0) != 1)
// 		{
// 			if (!ft_strncmp(av[1], ">", ft_strlen(av[1])))
// 			{
// 				char **res = {av[1], "NULL"};
// 				n->outfile = ft_2dstrdup(res);
// 			}
// 			else if (!ft_strncmp(av[1], "<", ft_strlen(av[1])))
// 				n->infile = ft_strdup(av[2]);
// 			else if (ft_strchr(av[1], '-'))
// 			{
// 				n->opts = malloc(sizeof(char *) * (1 + 1));
// 				if (!n->opts)
// 				{
// 					printf("malloc failed\n");
// 					return ;
// 				}
// 				n->opts = ft_2dstrcpy(n->opts, av + 1, 1);
// 				if (!n->opts)
// 					printf("no opts in your code");
// 				n->arg = ft_2dstrdup(av + 2);
// 				if (!n->arg)
// 					printf("no args in your code\n");
// 			}
// 			else
// 			{
// 				n->arg = ft_2dstrdup(av + 1);
// 				if (!n->arg)
// 					printf("no args in your code\n");
// 			}
// 			n->ex_code = 0;
// 			to_free2(av);
// 		}
// 	}
// 	else
// 	{
// 		n->cmd = NULL;
// 		n->outfile = NULL;
// 		n->infile = NULL;
// 		if (!ft_strncmp(av[0], ">", ft_strlen(av[0])))
// 			n->outfile = ft_strdup(av[1]);
// 		else if (!ft_strncmp(av[0], "<", ft_strlen(av[0])))
// 			n->infile = ft_strdup(av[1]);
// 	}
// }

t_list *new_prs(char *cmd, char **opts, char *args)
{
	t_prs *new;
}

void	set_values(t_prs *p)
{
	t_prs *p1;

	p->cmd = "ls";
	p->ex_code = 0;
	p->arg = NULL;
	p->opts = NULL;
	p->in = NULL;
	p->in_f = NULL;
	p->out = NULL;
	p->out_f = NULL;
	p->next = 
	
		
}


int main(int ac, char **av, char **env)
{
	char	*input;
	t_prs	n;
	t_list	*envp;

	envp = ft_envdup(env);
	if (!envp || ac == -1 || !av)
		return (1);// malloc failed;
	while (1)
	{
		input = readline("minishell$ ");
		if (input == NULL)
			return (ft_printf("exit\n"), 0);
		if (input[0] != '\0')
		{
		//set_values(&n, input);
		set_values(&n);
		n.ex_code = start_exec(&n, envp);
		if (input[0] != '\0')
			add_history(input);
		}
		printf("your exit code == %d\n", n.ex_code);
		free(input);
	}
}
