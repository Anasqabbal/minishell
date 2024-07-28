/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:36:33 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/28 16:17:43 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
# include <readline/history.h>
# include <readline/readline.h>


void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 1;
		printf("\n");
		// rl_replace_line("", 0);
		rl_on_new_line();     
    	rl_redisplay();
	}
}
void	ft_handler_fork(int sig)
{
	// puts("jhhhgjggghugug");
	if (sig == SIGINT)
	{
		printf("\n");
	}	
}
void ft_handler_here(int sig)
{
	
	if (sig == SIGINT)
	{
		close(0);
		printf("\n");	
	}
}
/*
minishell ✗ << $USER$$USER$f

➜ minishell ✗ export f=
➜ minishell ✗ > $f

➜ minishell ✗ << $$$f

➜ minishell ✗ << $?

➜ minishell ✗ < $fefe

➜ minishell ✗ export f=$UewfewR
➜ minishell ✗ > $f

*/