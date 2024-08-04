/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/04 15:27:37 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

static int	first_check_main(char **env, int *ret, t_list **envp, char **path)
{
	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
		return (write(2, "error\n", 6), exit(1), -1);
	rl_catch_signals = 0;
	*envp = ft_envdup(env, path);
	if (!(*envp))
		return (-1);
	ret = 0;
	return (0);
}

static int	quit_minishell(int *ret)
{
	if (g_sig == 1)
	{
		*ret = 1;
		g_sig = 0;
	}
	return (1);
}

static int	start_minishell(t_list **envp, int *ret, char **path, t_prs *n)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input && printf("exit\n"))
		return (quit_minishell(ret));
	if (input[0] == '\0')
	{
		free(input);
		return (2);
	}
	if (input && input[0] != '\0')
	{
		if (g_sig == 1)
		{
			*ret = 1;
			g_sig = 0;
		}
		check_syntax(input, (*envp), &n, ret);
		*ret = start_exec(&n, envp, *ret, path);
		if (input[0] != '\0')
			add_history(input);
		clear_prs(&n);
		free(input);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	int		r;
	char	*path;
	int		ret;
	t_prs	*n ;
	t_list	*envp;

	if (first_check_main(env, &ret, &envp, &path) == -1)
		return (1);
	(void) av;
	n = NULL;
	while (1 || ac)
	{
		r = start_minishell(&envp, &ret, &path, n);
		if (r == 2)
			continue ;
		if (r == 1)
			break ;
	}
	return (ft_lstclear(&envp, free), clear_prs(&n), ret);
}
