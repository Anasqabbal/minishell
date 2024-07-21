/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipping_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:43 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/20 16:55:26 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int count_it(char *str)
{
	int count;
	int x;

	count = 0;
	x = 0;
	while (str[x])
	{
		if (str[x] == '$' && ft_isdigit(str[x + 1]))
			count++;
		x++;
	}
	return (count);
}
char *blurr_dollar(char *str)
{
	int x;
	char *cmd;
	int y;
	
	x = 0;
	y = 0;
	cmd = malloc((ft_strlen(str) - (count_it(str) * 2) + 1) * sizeof(char));
	if (!cmd)
	{
		free(str);
		exit(1);
	}
	while (str[x])
	{
		if (str[x] == '$' && ft_isdigit(str[x + 1]))
			x += 2;
		else 
			cmd[y++] = str[x++];
	}
	cmd[y] = '\0';
	return (free(str), cmd);
}
static void	dollar_while(char *str, char *cmd, int *y)
{
	int count;
	int x;
	// int coun;

	x = 0;
	while (str[x] != '\0') 
	{
        count = 0;
        if (str[x] == '$') 
		{
            if ((str[x + 1] == '"' || str[x + 1] == '\'') && !turn_dollar(str, x))
                x++;
			else 
			{
               	while (str[x] != '\0' && str[x] == '$') 
				{
                    count++;
                    x++;
                }
                if (count % 2 != 0) 
                    cmd[(*y)++] = '$';
			}
        }
		else 
            cmd[(*y)++] = str[x++];
	}
}

// static void dollar_while(char *str, char *cmd, int *y)
// {
// 	int x;
// 	int count;

// 	x = 0;
// 	while (str[x])
// 	{
		
// 		if (str[x] == '>' && str[x + 1] == '>')
// 		{
// 			if (str[x + 3] == '$' && str[x])
// 			{

// 			}
// 		}
// 		else if ((str[x] == '<' && str[x + 1] != '<') || (str[x] == '>' && str[x + 1] != '>'))
// 		{
// 			if (str[x + 2] == '$' && str[x])
// 			{
// 				printf("QQ1\n");
// 			}
// 		}
// 		else if (str[x] == '<' && str[x + 1] == '<')
// 		{
// 			if (str[x + 3] == '$' && str[x])
// 			{
// 				printf("QQ2\n");
// 			}
// 		}
// 		else
// 		{
// 			if (str[x] == '$') 
// 			{
// 				count = 0;
//             	if ((str[x + 1] == '"' || str[x + 1] == '\'') && !turn_dollar(str, x))
//                 x++;
// 				else 
// 				{
// 					printf("jeff\n");
//                		while (str[x] != '\0' && str[x] == '$') 
// 					{
//                     	count++;
//                     	x++;
//                 	}
//                		if (count % 2 != 0) 
//                     	cmd[(*y)++] = '$';
// 				}	
//         	}
// 			else 
//            		cmd[(*y)++] = str[x++];
// 		}
// 		if(str[x])
// 			x++;
// 	}
// }

char *dollar_sign(char *str)
{
    char *cmd;
    int y;

    y = 0;
    cmd = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (!cmd) 
	{
        free(str);
        exit(1);
    }
	dollar_while(str, cmd, &y);
    cmd[y] = '\0';
  	return (free(str), cmd);
}