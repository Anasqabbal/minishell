/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:43:32 by zgtaib            #+#    #+#             */
/*   Updated: 2024/06/29 08:31:39 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *dollar_sign(char *str)
{
    int x;
    char *cmd;
    int count;
    int y;

    x = 0;
    y = 0;
	turn_single(str, 1);
    cmd = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (!cmd)
    {
        free(str);
        exit(1);
    }
    while (str[x] != '\0')
    {
        count = 0;
        if (str[x] == '$')
        {
            while(str[x] != '\0' && str[x] == '$')
            {
                count++;
                x++;
            }
			if (count % 2 != 0)
            	cmd[y++] = '$';
        } 
		else
        {
            if (str[x] == '$' && str[x + 1] == '"')
                x++;
			cmd[y++] = str[x++];
        }
    }
    cmd[y] = '\0';
	turn_single(cmd, 1);
  return (free(str), cmd);
}
static char *expand_variable(char *str, t_list *env, int *ndx)
{
	char *hold;
	t_list *expa;   
	int len;

	hold = ft_strjoin(str, "=");
	if(!hold)
		return(free(str), NULL);
	len = ft_strlen(hold);
	expa = ft_getenvza(hold, env);
	if (!expa)
	{
		(*ndx) = 1;
		return (free(hold), NULL);
	}	
	hold = ft_strdup(expa->content);
	return (hold + len);
}
static char *extract_virable(char *str, int *var_len)
{
	int x;
	char *var;
	int y ;

	x = 0;
	str++;
	while (ft_isalnum(str[x]) || str[x] == '_')
		x++;
	var = (char *)malloc((x + 1) * sizeof(char));
	if (!var)
		return(free(str), NULL);
	y = 0;
	while (y < x)
	{
		var[y] = str[y];
		y++;
	}
	var[y] = '\0';
	(*var_len) = x;
	return (var);
}
static int calaculate_expan_len(char *str, t_list *env)
{
	int x;
	int y;
 	int single_quotes = 0;
    int double_quotes = 0;
	int len;
	int var_len;
	int ndx;
	char *var;
	char *expans;

	len = 0;
	x = 0;
	while ((size_t)x < ft_strlen(str))
	{
		if (str[x] == '\'' && !double_quotes)
		{
			single_quotes = !single_quotes;
			len++;
			x++;
		}
		else if(str[x] == '"' && !single_quotes)
		{
			double_quotes = !double_quotes;
			len++;
			x++;
		}
		if (str[x] == '$' && !single_quotes)
		{
			var = extract_virable(&str[x], &var_len);
			ndx = 0;
			expans = expand_variable(var, env, &ndx);
			free(var);
			if (expans)
			{
				len += ft_strlen(expans);
				x += var_len + 1;
			}
			else if(!expans && ndx == 0)
			{
				free(str);
				exit(1);
			}
			else
			{
				len++;
				x ++;
				y = 0;
				while (y < var_len)
				{
					len++;
					y++;
				}
				x += var_len;
			}
		}
		else
		{
			len++;
			x++;
		}
	}
	return (len);
}

char *cmd_expa(char *str, t_list *env)
{
	char *cmd;
	int y;
	int single_quotes;
    int double_quotes;
	int x;
	int var_len;
	char *var;
	char *expans;
	int ndx;

	x = 0;
	y = 0;
	single_quotes = 0;
	double_quotes = 0;
	cmd = (char *)malloc((calaculate_expan_len(str, env) + 1) * sizeof(char));
	if (!cmd)
	{
		free(str);
		exit(0);
	}
	while ((size_t)x < ft_strlen(str))
	{
		if (str[x] == '\'' && !single_quotes)
		{
			single_quotes = !single_quotes;
			cmd[y++] = str[x++];
		}
		else if(str[x] == '"' && !single_quotes)
		{
			double_quotes = !double_quotes;
			cmd[y++] = str[x++];
		}
		if (str[x] == '$' && !single_quotes)
		{
			if (str[x + 1] == '$')
            {
                cmd[y++] = '$';
                x += 2;
            }
			else 
			{
				var_len = 0;
				var = extract_virable(&str[x], &var_len);
				ndx = 0;
				expans = expand_variable(var, env, &ndx);
				free(var);
				if (expans)
				{
					ft_strcpy(&cmd[y], expans);
					y += ft_strlen(expans);
					x += var_len + 1;
				}	     
				else if (!expans && ndx == 0)
				{
					free(cmd);
					free(str);
					exit(1);
				}
				else if ((size_t) x < ft_strlen(str))
					x+= var_len + 1;
			}
		}	
		else if ((size_t) x < ft_strlen(str))
				cmd[y++] = str[x++];
	}
	cmd[y] = '\0';
	return (free(str), cmd);
}

