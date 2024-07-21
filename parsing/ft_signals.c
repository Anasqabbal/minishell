/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/29 15:36:33 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/20 16:45:48 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_handler(int sig)
{
	(void)sig;
	printf("\n");
	rl_replace_line("", 0); 
	rl_on_new_line();     
    rl_redisplay();
}
