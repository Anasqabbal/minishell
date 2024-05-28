/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/10 14:38:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/28 15:39:10 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// int main(int ac, char **av, char **env)
// {
// 	int fd;

// 	close(0);
	
// 	fd = open("outfile", O_RDONLY);
// 	if (fd < 0)
// 		return (perror("open"), 1);
// 	printf("the value of fd  == %d\n", fd);
// 	close(fd);
// 	int fd2 = open("/dev/stdin", O_RDONLY);
// 	if (fd2 < 0)
// 		return (perror("open 2"), 1);
	// printf("the value of fd2 == %d\n", fd2);
	// // if (dup2(fd2, fd) < 0)
	// // 	return (perror("dup2"), 1);
	// // close(fd2);
	// int fd3 = dup2(fd2, fd);
	// printf("the value of fd3 == %d\n", fd3);
	// execve("/usr/bin/grep", av + 1, env);

	// printf("the value of fd3 == %d\n", fd3);
	// int pid = fork();
	// if (pid == 0)
	// else
	// 	wait(NULL);
// }


// #include <stdio.h>
// #include <fcntl.h>
// #include <unistd.h>
// #include <errno.h>

// int main(int ac, char **av, char **env)
// {
//     int fd;

//     // Closing stdin (fd 0)
//     if (close(0) < 0) {
//         perror("close stdin");
//         return 1;
//     }

//     // Open "outfile" and expect it to take fd 0
//     fd = open("outfile", O_RDONLY);
//     if (fd < 0) {
//         perror("open");
//         return 1;
//     }
//     printf("the value of fd == %d\n", fd);

//     // Close the opened file
//     if (close(fd) < 0) {
//         perror("close");
//         return 1;
//     }

//     // Reopen stdin
//     int fd2 = open("/dev/stdin", O_RDONLY);
//     if (fd2 < 0) {
//         perror("open 2");
//         return 1;
//     }

//     // Optional: Verify if fd2 is 0
//     if (fd2 != 0) {
//         fprintf(stderr, "Error: expected fd2 to be 0, got %d\n", fd2);
//         close(fd2);
//         return 1;
//     }

//     // Close the reopened stdin
//     close(fd2);

//     return 0;
// }


#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

static int ft_strlen_(char *s)
{
	int i;
	i = -1;
	while(s[++i]);
	return (i);
}

static char *correct_it(char *s)
{
	int len;
	char *res;
	int		i;
	int 	j;

	i = -1;
	j = 1;
	len = ft_strlen_(s) - 2;
	res = malloc(sizeof(char) * (len + 1));
	if (!res)
		return (NULL);
	while(++i < len)
		res[i] = s[j++];
	res[len] = '\0';
	return (res);
}

int main(int ac, char **av, char **env)
{
	char *res = "\"hello\"";
	char *res2;

	res2 = correct_it(res);
	printf("res == %s\n", res2);
}
