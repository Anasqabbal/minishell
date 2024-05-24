/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:38:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/22 16:54:20 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void to_free(char **res)
{
	int i;
	i = -1;
	while (res[++i])
		free(res[i]);
	free(res);
}

void f(void){system("leaks minishell");}

char **set_file_names(char **av, int len)
{
	int len2;
	char **f_n;
	int		i;

	i = -1;
	f_n = malloc (sizeof(char *) * (len + 1));
	if (!f_n)
		return (NULL);
	while(++i < len)
	{
		len2 = ft_strlen(av[i]);
		f_n[i] = malloc(sizeof(char) * (len2 + 1));
		if (!f_n[i])
			return (NULL);
		ft_memcpy(f_n[i], av[i], len2);
		f_n[i][len2] = '\0';
	}
	return (f_n);
}

char **set_value(char *s, int r_n)
{
	char **red;
	int i;

	i  = 0;
	if (r_n == 0)
		return (NULL);
	red = malloc(sizeof(char *) * (r_n + 1));
	if (!red)
		return (NULL);
	while (i < r_n)
	{
		red[i] = malloc(sizeof(char) * (2));
		if (!red[i])
			return (NULL);
		ft_memcpy(red[i], ">", 1);
		red[i][1] = '\0';
		i++;
	}
	red[r_n] = NULL;
	return (red);
}

void	execute_it(char **red, char **fileout, char **cmd, char **env)
{
	char **cmd2;
	char *path;
	int		pid;

	printf("your cmd == %s\n", cmd[0]);
	cmd2 = ft_split(cmd[0], ' ');
	if (!cmd2)
		return ;
	path = ft_strjoin("/usr/bin/", cmd2[0]);
	if (!path)
		return ;
	printf("your path == %s\n", path);
	
	
	int len1, len2;
	len1 = calcul_args(red);
	printf("the len of your redirections is %d\n", len1);
	len2 = calcul_args(fileout);
	printf("the len of your files is %d\n", len2);
	
	printf("fileout[%d] == %s\n", (len2 - 1), fileout[len2 - 1]);
	int fd = open(fileout[len2 - 1], O_RDONLY);
	if (fd < 0)
	{
		printf("open failed\n");
		exit (1);
	}
	
	/*execution part*/
	pid = fork();
	if (pid < 0)
		return ;
	if (pid == 0)
	{
		if (dup2(fd, STDIN_FILENO) < 0)
		{
			printf("dup2 failed\n");
			exit (1);
		}
		int i = -1;
		while (cmd2[++i])
			printf("your command[%d] == %s\n", i, cmd2[i]);
		execve(path, cmd2, env);
	}
	else
		wait(NULL);
}

int main(int ac, char **av, char **env)
{
	t_list *envp;
	int		ret;
	(void)ac;
	char **red;
	char **fileout;
	int		i;

	if (ac == 1)
		return (printf("enter valide arguments\n"), 1);
	envp = ft_envdup(env);
	if (!envp)
		return (NULL, 1);
	
	red = set_value(">", ft_atoi(av[1]));
	fileout = set_file_names(av + 2, ft_atoi(av[1]));
	i = -1;
	// while (red[++i])
	// 	printf("your red is %s\n", red[i]);
	// 	i = -1;
	// while (fileout[++i])
	// 	printf("your fileout is %s\n", fileout[i]);
	execute_it(red, fileout, av + (ft_atoi(av[1]) + 2), env);
	to_free(fileout);
	to_free(red);
	ft_lstclear(&envp, free);
}