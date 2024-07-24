/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/24 16:15:17 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	f(void)
{
	system("leaks minishell");
}

int main(int ac, char **av, char **env)
{
	char	*input;
	char	*path;
	int		ret;
	t_prs	*n ;
	t_list	*envp;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
	{
		write(2, "error\n", 6);
		exit(1);
	}
	rl_catch_signals = 0;
	// envp = NULL;
	// atexit(f);
	envp = ft_envdup(env, &path);
	if (!envp || ac == -1 || !av)
		return (1);// malloc failed;
	ret = 0;
	n = NULL;
	while (1)
	{
		input = readline("minishell$ ");
		if (!input && printf("exit\n"))
			break ;
		if (input && input[0] != '\0')
		{
			check_syntax(input, envp, &n, &ret);
			// print_prs(n);
			ret = start_exec(&n, &envp , ret, &path);
			if (input[0] != '\0')
				add_history(input);
			clear_prs(&n);
			free(input);
		}
	}
	return (ft_lstclear(&envp, free), clear_prs(&n), ret);
}