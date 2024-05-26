#include "minishell.h"

void to_free__(char **cmd)
{
	if (cmd)
	{
		int i = -1;
		while(cmd[++i])
			free(cmd[i]);
		free(cmd);
	}
}

int main(int ac, char **av, char **env)
{
	int fd[2];
	char *path;
	char **cmd;
	int pid;

	if (pipe(fd) < 0)
		return (perror("pipe"), 1);
	
	path = ft_strdup(av[1]);
	if (!path)
		return(printf("malloc failed\n"), 1);
	cmd = ft_split(av[2], ' ');
	if (!cmd)
		return(printf("malloc failed\n"), 1);

	pid = fork();
	if (pid < 0)
		return (perror("fork()"), 1);

	if (pid == 0)
	{
		close(fd[1]);
		char buf[100];
		read(fd[0], buf, 100);
		//write (fd[1], "nothing", 7);
		if (execve(path, cmd, env) < 0)
			return(perror("execve"), 1);
	}
	else
	{
		int fd2;

		fd2 = dup(fd[1]);
		close(fd[1]);
		close(fd2);
		wait(NULL);
		// char buf[100];
		// read(fd[0], buf, 100);
	}

	// char buf[100];
	// if (read (fd[0], buf, 100) < 0)
	// 	return (perror("read"), 1);
	
	//write(fd[1], "hello", 5);

	// if (execve(path, cmd, env) < 0)
	// 	return(perror("execve"), 1);

	free(path);
	to_free__(cmd);
}