/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:14:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/26 10:48:35 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include <sys/wait.h>
#include "minishell.h"
#include <errno.h>

/*CREAT A LIST AND PRINT IT*/

	// /*creat a list*/
	// t_list *h1, *h2, *h3, *h4, *h5;
	// t_list *tmp;
	
	// h1 = ft_lstnew(ft_strdup("first node"));
	// h2 = ft_lstnew(ft_strdup("second node"));
	// h3 = ft_lstnew(ft_strdup("third node"));
	// h4 = ft_lstnew(ft_strdup("fourth node"));
	// h5 = ft_lstnew(ft_strdup("fifth node"));

	// ft_lstadd_back(&h1, h2);
	// ft_lstadd_back(&h1, h3);
	// ft_lstadd_back(&h1, h4);
	// ft_lstadd_back(&h1, h5);

	// /*print your list*/
	// tmp = h1;
	// while (tmp)
	// {
	// 	printf("the len of your node is %d\n", ft_lstsize(tmp));
	// 	tmp = tmp->next;
	// }



/*READ FROM HERE DOC*/

static int check_file_access(char *file)
{
	if (file)
	{
		if (access(file, F_OK))
		{
			if (access(file, R_OK))
				return (0);
			else
				return (13);//permision denied
		}
		else
			return (2); //file not found;
	}
	return(0);
}
void to_free_f(int **file, int len)
{
	int cl;

	while(file && --len >= 0)
	{
		if (file[len][0] >= 0)
			close (file[len][0]);
		free(file[len]);
	}
	free(file);
}

static int	creat_open_file(char *f1, int ind, int VAL)
{
	int	fd;

	if (ind == 0)
		fd = open(f1, O_RDONLY);
	else
		fd = open(f1, O_RDWR | VAL | O_CREAT, 0644);
	if (fd < 0)
	{
		perror("open");
		return (-1);
	}
	return (fd);
}

char	*read_from_here_doc(char *lim)
{
	char	*res;
	char	*here_doc;
	char	*tmp;

	here_doc = NULL;
	while(1)
	{
		ft_putstr_fd("> ", 0);
		res = get_next_line(0);
		if (!res || !ft_strncmp(res, lim, ft_strlen(lim)))
			break ;
		tmp = here_doc;
		here_doc = my_strjoin(here_doc, res);
		if (!here_doc)
			return (free(here_doc), free(res), NULL);
		free(res);
		free(tmp);
	}
	free(res);
	return (here_doc);
}

int ft_execve1(t_exec *e, int in, int out)
{
	int pid;

	pid  = fork();
	if (pid < 0)
		return (perror("fork"), 1);
	if (pid == 0)
	{
		if (in != -1)
			close(in);
		if (out != -1 && dup2(out, STDOUT_FILENO) < 0)
			return (perror("dup2(0)"), 1);
		if (out != -1)
			close(out);
		if (execve(e->path, e->cmd, e->env) < 0)
			return(perror("execve"), 1);
	}
	else if (pid)
	{
		if (in != -1 && dup2(in, STDIN_FILENO) < 0)
			return (perror("dup2(1)"), 1);
		if (in != -1)
			close(in);
		wait(NULL);
	}
	return (0);
}

int open_in_files(t_prs *p, t_exec *e)
{
	int	i;

	i = -1;
	e->in_l = calcul_args(p->in);
	if (!e->in_l)
		return (e->in = NULL, 0);
	e->in = malloc(sizeof(int *) * e->in_l);
	if (!e->in)
		return (1);// malloc failed;
	while(++i < e->in_l)
	{
		e->in[i] = malloc(sizeof(int));
		if (!e->in[i])
			return(to_free_f(e->in, i), 1); //free malloc before return; malloc failed;
		if (!ft_strncmp(p->in[i], "<<", 2))
		{
			e->in[i][0] = -1;
			e->here_doc = read_from_here_doc(p->in_f[i]);
		}
		else if (!ft_strncmp(p->in[i], "<", 1))
			e->in[i][0] = creat_open_file(p->in_f[i], 0, 0);
		if ((ft_strncmp(p->in[i], "<<", 2) && e->in[i][0] == -1))
			return (to_free_f(e->in, i), 1);
	}
	return (0);
}

static int  the_input(t_prs *lst, t_exec *e)
{
	int fd[2];

	if (!ft_strncmp(lst->in[e->in_l - 1], "<<", 2))
	{
		if (pipe(fd) < 0)
				return (perror("pipe"), 1); //close all files and free them;
		write(fd[1], e->here_doc, ft_strlen(e->here_doc));
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, 1);// close files descriptores and free its memory
		close(fd[0]);
		close(fd[1]);
	}
	else
	{
		printf("the e->in[%d][0] == %d and its name is %s\n", (e->in_l - 1), e->in[e->in_l - 1][0], lst->in_f[e->in_l - 1]);
		if(dup2(e->in[e->in_l - 1][0], STDIN_FILENO) < 0)
			return (perror("dup2"), lst->ex_code = 1, 1); // close files descriptores and free its memory
		close(e->in[e->in_l - 1][0]);
		e->in[e->in_l - 1][0] = -1;
	}
	return (lst->ex_code = 0, 0);
}

static int	one_cmd__(t_prs *lst, char **env, t_exec *e)
{
	int		ret;
	int		in;
	int		out;

	in = -1;
	out = -1;
	// ret = check_access(lst->cmd, e, envp);
	// if (ret)
	// 	return (ret);
	// if (ft_open_files(lst, e))
	// 	return (lst->ex_code);
	if (e->in)
	{
		if (the_input(lst, e))
			return (lst->ex_code);
	}
	if (e->out)
		out = e->out[e->out_l - 1][0];
	// e->cmd = prepare_cmd(lst->cmd, lst->opts, lst->arg);
	// e->env = from_lst_to_2d(envp);
	// if (!e->env)
	// 	return(printf("Error inside ft_exeve \n"), 1);// malloc failed
	return (lst->ex_code = ft_execve1(e, in, out));
}
// void f(void){system("leaks a.out");}

int main(int ac, char **av, char **env)
{
	// atexit(f);
	t_prs p;
	t_exec e;
	int i = 0;
	int j = 0;
	int k = 0;

	// p.in = malloc(sizeof(char *) * (3 + 1));
	// p.in_f = malloc(sizeof(char *) * (3 + 1));
	// while(++i < 7)
	// {
	// 	if (i % 2 != 1)
	// 		p.in_f[k++] = ft_strdup(av[i]);
	// 	else
	// 		p.in[j++] = ft_strdup(av[i]);
	// }
	// p.in_f[3] = NULL;
	// p.in[3] = NULL;

	// printf("your tokens :\n");
	// i = -1;
	// while(++i < 3)
	// 	printf("%s\n", p.in[i]);

	// printf("your files :\n");
	// i = -1;
	// while(++i < 3)
	// 	printf("%s\n", p.in_f[i]);

	p.in = NULL;
	p.in_f = NULL;
	e.here_doc = NULL;
	open_in_files(&p, &e);
	printf("your files descriptor is :\n");
	i = -1;
	// while(++i < 3)
	// 	printf("%d\n", e.in[i][0]);
	if (e.here_doc)
		printf("your here_doc is %s", e.here_doc);


	e.in = NULL;
	e.cmd = ft_2dstrdup(av + 1);
	e.path = "/usr/bin/grep";
	e.size = 1;
	e.env = env;
	e.out = NULL;
	e.out_l = 0;
	e.in_l = 0;

	one_cmd__(&p, env, &e);

	to_free_f(e.in, e.in_l);
	to_free(p.in);
	to_free(p.in_f);
	free(e.here_doc);
}