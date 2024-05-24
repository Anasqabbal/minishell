/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   simple_test.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/16 17:14:12 by anqabbal          #+#    #+#             */
/*   Updated: 2024/05/24 18:24:18 by anqabbal         ###   ########.fr       */
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



int main(int ac, char **av, char **env)
{

			t_exec e;
	char *her;

	if (ac == 1)
		return (printf("enter more args\n"), 1);
	else
	{
		if (!ft_strncmp(av[1], "<<", ft_strlen(av[1])))
		{
			her = read_from_here_doc(av[2]);
			if (!her)
				return(printf("here_doc failed\n"), 1);
		}
		int pid;
		int pi[2];

		if (pipe(pi) < 0)
			return (perror("pipe"), 1);
		write(pi[1], her, ft_strlen(her));
		pid = fork();
		if (pid < 0)
			return (perror("fork"), 1);
		if (pid == 0)
		{
			// write(0, her, ft_strlen(her));
			if (dup2(pi[0], STDIN_FILENO) < 0)
			{
				perror("dup2");
				exit(1);
			}
			if (execve("/usr/bin/grep", av + 3, env) < 0)
			{
				perror("execve");
				exit(1);
			}
		}
		else
		{
			close(pi[0]);
			close(pi[1]);
			wait(NULL);
		}
	}
		// int pid;

		// pid = fork();
		// if (pid < 0)
		// 	return (perror("fork"), 1);
		// if (pid == 0)
		// {
		// 	exit(0);
		// 	// execve("/usr/bin/grep", av + 3, env);
		// }
		// else
		// 	wait(NULL);
		
}