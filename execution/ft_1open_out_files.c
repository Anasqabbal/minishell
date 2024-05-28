/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_out_files.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 16:49:28 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/28 16:05:53 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_restore_input(void)
{
	int fd2;
	
	close(0);
	fd2 = open("/dev/tty", O_RDONLY);
	if (fd2 < 0) 
	{
		printf("ft_1open_out_files.c, ft_restore_input()\n");
		perror("open");
		return (1);
	}	
	return (0);
}

int	ft_error_files(int indice, int ret, char *n)
{
	ft__putstr_fd("minishell: ", 2);
	ft__putstr_fd(n, 2);
	if (indice == 13)
		ft_putendl_fd(": Permission denied", 2);
	else if (indice == 2)
		ft_putendl_fd(": No such file or directory", 2);
	return (ret);
}

int	creat_open_file(char *f1, int ind, int VAL)
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
int open_out_files(t_prs *p, t_exec *e)
{
	int	i;

	i = -1;
	e->out_l = calcul_args(p->out);
	if (!e->out_l)
		return (e->out = NULL, 0);
	e->out = malloc(sizeof(int *) * e->out_l);
	if (!e->out)
		return (1);// malloc failed;
	while(++i < e->out_l)
	{
		e->out[i] = malloc(sizeof(int));
		if (!e->out[i])
			return(to_free_f(e->out, i), 1); //free malloc before return; malloc failed;
		if (!ft_strncmp(p->out[i], ">>", 2))
			e->out[i][0] = creat_open_file(p->out_f[i], 1, O_APPEND);
		else if (!ft_strncmp(p->out[i], ">", 1))
			e->out[i][0] = creat_open_file(p->out_f[i], 1, O_TRUNC);
		if (e->out[i][0] < 0)
			return (to_free_f(e->out, i), 1);
	}
	return (0);
}

// void f(void){system("leaks p");}

// int main(int ac, char **av)
// {
// 	atexit(f);
// 	t_prs p;
// 	t_exec e;
// 	int i = 0;
// 	int j = 0;
// 	int k = 0;

// 	p.out = malloc(sizeof(char *) * (3 + 1));
// 	p.out_f = malloc(sizeof(char *) * (3 + 1));
// 	while(++i < 7)
// 	{
// 		if (i % 2 != 1)
// 			p.out_f[k++] = ft_strdup(av[i]);
// 		else
// 			p.out[j++] = ft_strdup(av[i]);
// 	}
// 	p.out_f[3] = NULL;
// 	p.out[3] = NULL;

// 	printf("your tokens :\n");
// 	i = -1;
// 	while(++i < 3)
// 		printf("%s\n", p.out[i]);

// 	printf("your files :\n");
// 	i = -1;
// 	while(++i < 3)
// 		printf("%s\n", p.out_f[i]);

// 	open_out_files(&p, &e);
// 	printf("your files descriptor is :\n");
// 	i = -1;
// 	while(++i < 3)
// 		printf("%d\n", e.out[i][0]);
// 	to_free_f(e.out, e.out_l);
// 	to_free(p.out);
// 	to_free(p.out_f);
// }
