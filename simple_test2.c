/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_test2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 16:39:37 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/25 18:01:14 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int ac, char **av, char **env)
{
	int fd[2];
	char *res;
	char buf[346];
	int pid;

	buf[0] = '\0';
	if (pipe(fd))
		return(perror("pipe"), 1);
	pid  = fork();
	if (pid < 0)
		return(perror("fork"), 1);
	if (pid == 0)
	{
		if (write(fd[1], "hello", 5) < 0)
		{
			perror("write");
			exit(1);
		}
		// if (dup2(fd[1], STDOUT_FILENO) < 0)
		// {
		// 	perror("dup2");
		// 	exit(1);
		// }
		close(fd[1]); // if you don't close this write_end this processe will still waiting data from another processe so if you don't use it you must close it also 
		if (dup2(fd[0], STDIN_FILENO) < 0)
		{
			perror("dup2");
			exit(1);
		}
		close(fd[0]); // this read_end after dup close it I don't think it is a probleme, but you need to make some tests to see
		execve("/usr/bin/grep", av + 1, env);
	}
	else
	{
			if (close(fd[1]) < 0)
				return (perror("close"), 1);// if you don't close this pipe another processe will stay waiting the write_end to get some input, so if you don't use it you must close it
			// close(fd[0]);                // you see I don't close here(commented close(fd[0])) and the programe run successful hhhhhhh;
			if (wait(NULL) < 0)
				return (perror("wait"), 1);
			// close(0);
			close(1);
			// if (read(fd[0], buf, 123) < 0)
			// 	return(perror("read"), 1);
			if (printf("your buffer %s\n", buf) < 0)
				return(perror("printf"), 1);
	}
}