/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/27 16:41:34 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int g_sig;

void	f(void)
{
	system("leaks minishell");
}

// int here_doc_syntax(char *input)
// {
// 	char *res;
// 	int		i;

// 	i = 0;
// 	res = ft_strchr(input, '<');
// 	if (!res)
// 		return (258);
// 	else
// 	{
// 		if (res[i + 1] == '<' && (ft_isalnum(res[i + 2]) || ft_ ))
// 	}
	
// }

int main(int ac, char **av, char **env)
{
	char	*input;
	char	*path;
	int		ret;
	t_prs	*n ;
	t_list	*envp;
	// char *here_doc;

	signal(SIGINT, ft_handler);
	signal(SIGQUIT, SIG_IGN);
	if (!isatty(STDIN_FILENO))
	{
		write(2, "error\n", 6);
		exit(1);
	}
	// rl_catch_signals = 0;
	// envp = NULL;
	// atexit(f);
	if (ac == -1 || !av)
		return (1);
	envp = ft_envdup(env, &path); /* if malloc failed the programe free the necessary stufs and exit inside the ft_envdup */
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
			// if (!n && ret == 258 && ft_strnstr("<<", input, ft_strlen(input)))
			// 	here_doc_syntax(input);
			ret = start_exec(&n, &envp , ret, &path);
			if (input[0] != '\0')
				add_history(input);
			clear_prs(&n);
			free(input);
		}
		if (g_sig == 1)
		{
			ret = 1;
			g_sig = 0;
		}
	}
	return (ft_lstclear(&envp, free), clear_prs(&n), ret);
}

