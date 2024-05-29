/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:38:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/29 17:12:37 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

// static int ft_strlen_(char *s)
// {
// 	int i;
// 	i = -1;
// 	while(s[++i]);
// 	return (i);
// }

// static char *correct_it(char *s)
// {
// 	int len;
// 	char *res;
// 	int		i;
// 	int 	j;

// 	i = -1;
// 	j = 1;
// 	len = ft_strlen_(s) - 2;
// 	res = malloc(sizeof(char) * (len + 1));
// 	if (!res)
// 		return (NULL);
// 	while(++i < len)
// 		res[i] = s[j++];
// 	res[len] = '\0';
// 	return (res);
// }

int main(int ac, char **av, char **env)
{
	int ret;
	int res;
	int fd[2];
	int fd2[2]
	int pid ;
	
	pid = fork();
	if (pid < 0)
		return (perror("pid"), 1);
	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	write(fd[1], "hello", 5);
	if (pid == 0)
	{
		close(fd[1]);
		if (dup2(fd[0], STDIN_FILENO) < 0)
			return (perror("dup2"), 1);
		close(fd[0]);
		execve(av[1], av + 2, env);
	}	
	else
	{
		close(fd[1]);
		waitpid(pid, &ret, 0);
		printf("your processe exit with %d\n", WEXITSTATUS(ret));
	}
}
