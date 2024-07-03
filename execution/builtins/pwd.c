/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/06 17:48:57 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/28 16:39:05 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"



void ft_pwd(t_list *env, char **str)
{
	t_list *pwd;
	char *pwdd;
	
	if (str[0] != NULL)
	{
		printf("pwd: too many arguments\n");
		return ;
	}
	pwd = ft_getenv("PWD=", env);
	pwdd = ft_strdup(pwd->content);
	printf("%s\n", pwdd + ft_strlen("PWD="));
	free(pwdd);
}
//  int main(int ac, char **av, char **env)
// {
// 	char *res;
// 	t_list *env1;
// 	int i;
// 	i = 0;
// 	env1  = ft_envdup(env);
// 	char *str[] = {NULL};
// 	pwd(env1, str);
// 	if (!env1)
// 		return (1);
// 	// while (env1 != NULL)
// 	// {
// 	// 	printf("%s\n", env1->content);
// 	// 	env1 = env1->next;
// 	// }
	
// 	return (0);
// } 