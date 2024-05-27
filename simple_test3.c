#include "minishell.h"
#include <errno.h>

typedef struct s_test
{
	char *path;
	char **env;
	char **cmd;
}t_test;


int ft_execve1(t_test *e, int in, int out)
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


int main(int ac, char **av, char **env)
{
	int pid;
	int fd[2];
	char **cmd1;
	char **cmd2;
	int		in;
	int 	out;
	t_test	e;

	in = -1;
	out = -1;
	cmd1 = ft_split(av[1], ' ');
	if (!cmd1)
		return (1);
	
	cmd2 = ft_split(av[2], ' ');
	if (!cmd2)
		return (1);

	if (pipe(fd) < 0)
		return (perror("pipe"), 1);

	// printf("the value of the fd[0] == %d fd[1] == %d\n\n", fd[0], fd[1]);
	int i = -1;
	while(++i < 2)
	{
		if (i == 0)
		{
			e.cmd = cmd1;
			e.env = env;
			e.path = "/bin/ls";
			
			out = fd[1];
			in = open(av[3], O_RDWR);
			// out = in;
			//in = fd[0];
		}
		else if (i == 1)
		{
			if (fd[1] != -1)
			{
				close(fd[1]);
				fd[1] = -1;
			}
			// close(in);
			// close(out);
			e.cmd = cmd2;
			e.env = env;
			e.path = "/usr/bin/grep";
			in = -1;
			out = -1;
			//out = open(av[3], O_RDWR);
			// close(fd[0]);
			printf("the value of av[3] == %s\n",av[3]);
		}
		printf("out == %d\nin == %d\n", out, in);
		ft_execve1(&e, in, out);
	}
}