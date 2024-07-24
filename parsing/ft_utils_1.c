/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:44:34 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/20 16:46:08 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void turn_single(char *str, int ndx)
{
	int x;
	char hold;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '\'')
        {
          	hold = str[x];
            x++;
			if (str[x] == '\0')
				break ;
           	while (str[x] != '\0')
            {
				if (str[x] == hold)
                    break ;
				if (ndx == 1)
					str[x] *= -1;
				if (str[x])
                	x++;
            }
		}
		if (str[x])
			x++;
	}
}
void	ft_strcpy(char *s1, char *s2)
{
	int x = 0;
	while ((size_t)x < ft_strlen(s2))
	{
		s1[x] = s2[x];
		x++;
	}
	s1[x] = '\0';
}

t_prs	*init_prs(void) 
{
    t_prs *new_node = (t_prs *)malloc(sizeof(t_prs));
    if (!new_node)
        return NULL;
    new_node->cmd = NULL;
    new_node->opts = NULL;
    new_node->arg = NULL;
	new_node->red = NULL;
    new_node->ex_code = 0;
    new_node->next = NULL;
    return new_node;
}

void back_turning(char **array)
{
	int y;

	y = 0;
	while (array[y])
	{
		turn_back(array[y], 1);
		y++;
	}
}

int	error_msg1h3(char *str, int x)
{
	if (!ft_strncmp(&str[x], "&", ft_strlen("&")) || !ft_strncmp(&str[x], "& &", ft_strlen("& &")))
	{
		write(2, "minishell: syntax error near unexpected token `&'\n", 51);
		return (0);
	}
	else if(!ft_strncmp(&str[x], "||", ft_strlen("||")))
	{
		write(2, "minishell: syntax error near unexpected token `||'\n", 52);
		return (0);
	}
	else if(!ft_strncmp(&str[x], "( (", ft_strlen("( (")) ||
		!ft_strncmp(&str[x], "((", ft_strlen("((")) ||
		!ft_strncmp(&str[x], "(", ft_strlen("(")))
	{
		write(2, "minishell: syntax error near unexpected token `'\n", 51);
		return (0);
	}
	else if(!ft_strncmp(&str[x], ") )", ft_strlen(") )")) ||
		!ft_strncmp(&str[x], "))", ft_strlen("))")) ||
		!ft_strncmp(&str[x], ")", ft_strlen(")")))
	{
		write(2, "minishell: syntax error near unexpected token `)'\n", 51);
		return (0);
	}
	return (1);
}
