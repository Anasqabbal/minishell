/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:36:33 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/01 15:01:49 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handler(int sig)
{
	if (sig == SIGINT)
	{
		g_sig = 1;
		printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	ft_handler_fork(int sig)
{
	(void)sig;
	g_sig = 1;
	// rl_catch_signals = 0;
}

void	ft_handler_here(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		printf("\n");
	}
}
