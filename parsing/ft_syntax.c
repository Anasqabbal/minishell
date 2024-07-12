/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_syntax.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:12:54 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/03 12:55:10 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		e_w_e_m(void)
{
	write(2, "syntax error\n", 13);
	return (0);
}

static char	*ft_syntax_h3(char *str, int x)
{
	char hold;

	while ((size_t)x < ft_strlen(str))
	{
		if (str[x] == '"' || str[x] == '\'')
        {
            hold = str[x];
            x++;
			if (str[x] == '\0')
				break ;
            while ((size_t)x < ft_strlen(str))
            {
				if (str[x] == hold)
                    break ;
				str[x++] *= -1;
            }
		}
		if (!ft_syntax_h1(str, &x))
			return (NULL);
		if (!ft_syntax_h2(str, x))
			return (NULL);
		x++;
	}
	return (str);
}

static char	*ft_syntax_h(char *stl, int *x)
{
	int len;
	char *str;

	len = ft_strlen(stl);
	while ((stl[len - 1] == ' ' || (stl[len - 1] >= 9 && stl[len - 1] <= 13)) && len > 1)
		len--;	
  	if (stl[len - 1] == '|' || stl[len - 1] == '<' || stl[len - 1] == '>') 
        return(0);
	str = replacewihte_s(stl);	
	while (str[(*x)] == ' ' || (str[(*x)] > 9 && str[(*x)] < 13))
		(*x)++;
	if (str[*x] == '|')
        return(0);
	return(str);
}
static char *ft_syntax(char *stl)
{
	int x;
	char *str;

	x = 0;
	str = ft_syntax_h(stl, &x);
	if (!str)
		return (NULL);
	str = ft_syntax_h3(str, x);
	if(!str)
		return(NULL);
	return (str);
}
int check_syntax(char *input, t_list *env, t_prs **node, int *ret)
{
	
	char *raw;
	char *cmd;
	int opp;
	int qts;

	opp = 0;
	qts = 0;
	if (input[0] == '\0')
		return (1);
	raw = ft_strdup(input);
	if(!raw)
		return (0);	
	cmd = ft_syntax(raw);
	if (!cmd)		
		return (free(cmd), 0, *ret = 258, e_w_e_m());	
	if(!check_qts(cmd, &opp, &qts))
		return (free(cmd), 0, *ret = 258, e_w_e_m());
	*node = pipe_split(cmd, opp, qts, env);
	return (1);
}

