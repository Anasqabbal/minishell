/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_in_files.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:35 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/28 18:15:28 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		**to_free_f(int **file, int len)
{
	while(file && --len >= 0)
	{
		if (file[len][0] >= 0)
			close (file[len][0]);
		free(file[len]);
		file[len] = NULL;
	}
	free(file);
	return(NULL);
}

void ft_clear_exec(t_exec *e)
{
	e->in = to_free_f(e->in, e->in_l);
	e->out = to_free_f(e->out, e->out_l);
	e->cmd = to_free(e->cmd);
	free(e->path);
	e->path = NULL;
	e->env = to_free(e->env);
	e->in_l = 0;
	e->out_l = 0;
	free(e->here_doc);
	e->size = 0;
}
static int check_file_access(char *file)
{
	if (file)
	{
		if (!access(file, F_OK))
		{
			if (!access(file, R_OK))
				return (0);
			else
				return (13);//permision denied
		}
		else
			return (ft_error_files(2, 1, file)); //file not found;
	}
	return(0);
}

char	*read_from_here_doc(char *lim, t_exec *e)
{
	char	*res;
	char	*here_doc;
	char	*tmp;

	(void)e;
	here_doc = NULL;
	while(1)
	{
		write(0, ">", 1);
		res = get_next_line(0);
		if (!res || !ft_strncmp(res, lim, ft_strlen(res) - 1))
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
			e->here_doc = read_from_here_doc(p->in_f[i], e);
		}
		else if (!ft_strncmp(p->in[i], "<", 1))
			e->in[i][0] = creat_open_file(p->in_f[i], 0, 0);
		if ((ft_strncmp(p->in[i], "<<", 2) && e->in[i][0] == -1))
			return (to_free_f(e->in, i), 1);
	}
	return (0);
}

int	ft_open_files(t_prs *lst, t_exec *e)
{
	int		len;
	int		i;
	int		ret;

	e->here_doc = NULL;
	e->in = NULL;
	e->out = NULL;
	len = calcul_args(lst->in);
	i = -1;
	while(++i < len)
	{
		if (ft_strncmp(lst->in[i], "<<", 2))
		{
			ret = check_file_access(lst->in_f[i]);
			if (ret)
				return (1);
		}
	}
	ret = open_in_files(lst, e);
	if (!ret)
		ret = open_out_files(lst, e);
	return (lst->ex_code = ret);
}

// void f(void){system("leaks a.out");}

// int main(int ac, char **av)
// {
// 	atexit(f);
// 	t_prs p;
// 	t_exec e;
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;

// 	p.in = malloc(sizeof(char *) * (3 + 1));
// 	p.in_f = malloc(sizeof(char *) * (3 + 1));
// 	while(++i < 7)
// 	{
// 		if (i % 2 != 1)
// 			p.in_f[k++] = ft_strdup(av[i]);
// 		else
// 			p.in[j++] = ft_strdup(av[i]);
// 	}
// 	p.in_f[3] = NULL;
// 	p.in[3] = NULL;

// 	printf("your tokens :\n");
// 	i = -1;
// 	while(++i < 3)
// 		printf("%s\n", p.in[i]);

// 	printf("your files :\n");
// 	i = -1;
// 	while(++i < 3)
// 		printf("%s\n", p.in_f[i]);

// 	open_in_files(&p, &e);
// 	printf("your files descriptor is :\n");
// 	i = -1;
// 	while(++i < 3)
// 		printf("%d\n", e.in[i][0]);
// 	printf("your here_doc is %s\n", e.here_doc);
// 	to_free_f(e.in, e.in_l);
// 	to_free(p.in);
// 	to_free(p.in_f);
// 	free(e.here_doc);
// }