/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/04 11:50:37 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	g_sig;

void	f(void)
{
	system("leaks minishell");
}

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

static int	start_minishell(t_list **envp, int *ret, char **path, t_prs *n)
{
	char	*input;

	input = readline("minishell$ ");
	if (!input && printf("exit\n"))
		return (1);
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
// void	handle_signals()
// {
// 	signal(SIGINT, ft_handler);
// 	signal(SIGQUIT, SIG_IGN);
// 	if (!isatty(STDIN_FILENO))
// 	{
// 		write(2, "error\n", 6);
// 		exit(1);
// 	}
// 	rl_catch_signals = 0;
// }
// void	read_line_loop(t_list *envp, int *ret, t_prs *n, char *path)
// {
// 	char	*input;
// 	while (1)
// 	{
// 		input = readline("minishell$ ");
// 		if (!input && printf("exit\n"))
// 			break ;
// 		if (g_sig == 1)
// 		{
// 			ret = 1;
// 			g_sig = 0;
// 		}
// 		if (input && input[0] != '\0')
// 		{	
// 			if (check_syntax(input, envp, &n, &ret) == -1)
// 			{
// 				ft_lstclear(&envp, free);
// 				free(input);
// 				exit(1);
// 			}
// 			add_history(input);
// 			// print_prs(n);	
// 			// exit(0);
// 			ret = start_exec(&n, &envp , ret, &path);
// 			clear_prs(&n);
// 		}
// 		free(input);
// 	}
// }
// int main(int ac, char **av, char **env)
// {
// 	char	*input;
// 	char	*path;
// 	int		ret;
// 	t_prs	*n ;
// 	t_list	*envp;

// 	envp = ft_envdup(env, &path);
// 	if (!envp || ac == -1 || !av)
// 		return (1);// malloc failed;
// 	ret = 0;
// 	n = NULL;
// 	return (ft_lstclear(&envp, free), clear_prs(&n), ret);
// }
