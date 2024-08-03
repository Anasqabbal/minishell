/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:36:33 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/30 19:22:09 by zgtaib           ###   ########.fr       */
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
	if (sig == SIGINT)
	{
		printf("\n");
	}
}

void	ft_handler_here(int sig)
{
	if (sig == SIGINT)
	{
		close(0);
		printf("\n");
	}
}
