/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expantion.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/28 15:43:32 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/29 15:28:11 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


static char *cmd_alloctation(char *str, t_list *env)
{
	char *cmd;

	// printf("%d\n", count_expantion_here(str));
	cmd = (char *)malloc((calaculate_expan_len(str, env) + count_expantion_here(str) + 1) * sizeof(char));
	if (!cmd)
	{
		free(str);
		exit(1);
	}
	return (cmd);
}
static char *extra_expa_var(char *str, t_list *env, int *var_len, int *ndx)
{
	char 	*var;
	char	*expans;

	var = extract_virable(str, var_len);
	expans = expand_variable(var, env, ndx);
	free(var);
	return(expans);
}
// void turn_single_exp(char *str, int ndx)
// {
// 	int x;
// 	char hold;

// 	x = 0;
// 	while (str[x] != '\0')
// 	{
// 		if (str[x] == '\'')
//         {
//           	hold = str[x];
// 			str[x] *= -1;
//             x++;
// 			if (str[x] == '\0')
// 				break ;
//            	while (str[x] != '\0')
//             {
// 				if (str[x] == hold)
// 				{
// 					str[x] *= -1;
//                     break ;
// 				}
// 				if (ndx == 1)
// 					str[x] *= -1;
// 				if (str[x])
//                 	x++;
//             }
// 		}
// 		if (str[x])
// 			x++;
// 	}
// }
void garbag_it(char *str)
{
	int x;

	x = 0;
	while (str[x])
	{
		str[x] *= -1;
		x++;
	}
}

static void handle_expa_suc(char *expans, char *cmd, t_ndx *ind, int var_len)
{	
	int x;
	int nd = 0;
	printf("-+%s+-\n", expans);
	turn_back(expans, 1);
	printf("-+%d+-\n", ind->ndx);
	char **hold = ft_split(expans, ' ');
	turn_back(expans, 1);
	if (arg_count(hold) > 1 && ind->ndx == 1)
	{
		char *hld = ft_strjoin("\"", expans);
		free(expans);
		expans = ft_strjoin(hld, "\"");
		free(hld);
		printf("-+%s+-\n", expans);
		nd = 1;
 	}
	else if (nd == 0)
	{
		ind->ndx = 0;
		printf("QQ\n");
		x = 0;
		while (expans[x])
		{
			if (expans[x] =='"' || expans[x] == '\'' || expans[x] == '$' || expans[x] == '|')
				expans[x] *= -1; 
			x++;
		}
	}
	ft_strcpy(&cmd[ind->y], expans);
	ind->y += ft_strlen(expans);
	ind->x += var_len + 1;
	free(expans);
}
int export_ambig(char *str, int x)
{
	int len = x - 1;
	int count = 0;
	while (len > 0 && (str[len] == '"' || ft_isalnum(str[len])))
	{	
		if (str[len] == '"')
			count++;
		len--;
	}
	if (len - 1 >= 0 && ((str[len - 1] == '>' || str[len - 1] == '<') && (count == 0 || count % 2 == 0)))
		return(0);
	return(1);
}
static void handle_var_exp(char *str, t_list *env, char *cmd, t_ndx *ind)
{
	int 	var_len;
	int 	ndx;
	char	*expans;
	int		z;

	var_len = 0;
	ndx = 0;
	expans = extra_expa_var(&str[ind->x], env, &var_len, &ndx);
	if (expans && expans[0] != '\0')
	{
		char **hold = ft_split(expans, ' ');

		int x;
		int count;

		count = arg_count(hold);
		free_it(hold, count);
		if (count > 1 && !export_ambig(str, ind->x))
		{
			printf("QQ1\n");
			x = 0;
			while (str[ind->x] && x < var_len + 1)
			{	
				cmd[ind->y++] = str[ind->x++];
				x++;
			}

		}
		else
		{ 	int len = ind->x - 1;
			int count = 0;
			while (len > 0 && (str[len] == '"' || ft_isalnum(str[len])))
			{	
			if (str[len] == '"')
				count++;
				len--;
			}
			if (count % 2 != 0 || count == 0)
				ind->ndx = 1;
			handle_expa_suc(expans, cmd, ind, var_len);
		}
	}
	else if(!expans && ndx == 0)
	{
		free(cmd);
		free(str);
		exit(1);
	}
	else
	{
		z = 0;
		if (ind->x - 2 >= 0 && (str[ind->x - 2] == '>' || str[ind->x - 2] == '<'))
		{
			printf("QQ\n");
			while (z < var_len + 1)
			{
				cmd[ind->y++] = str[ind->x++];
				z++;
			}
		}
		else
		{
			printf("++%c\n", str[ind->x]);
			ind->x += var_len + 1;
		}	
	}
}
int count_ex(char *cmd)
{
	int x;
	int count;

	count = 0;
	x = 0;
	while (cmd[x])
	{
		if (cmd[x] == '$' && cmd[x + 1] == '?')
			count++;
		x++;
	}
	return (count);
}
char *expand_ex_code(char *cmd, int *red)
{
	int x;
	int y;
	char *ex_code;
	char *str;
	int len;
	int count;

	ex_code = ft_itoa((*red));
	count = count_ex(cmd);
	len = ft_strlen(cmd) - (count * 2) + (ft_strlen(ex_code) * count);
	str = (char *)malloc((len + 2) * sizeof(char));
	if (!str)
	{
		free(ex_code);
		free(cmd);
		exit(1);
	}
	x = 0;
	y = 0;
	while (cmd[x])
	{
		if (cmd[x] == '$' && cmd[x + 1] == '?' && x - 3 >= 0 && cmd[x - 3] != '<' && cmd[x - 2] != '<')
		{
				ft_strcpy(&str[y], ex_code);
				y += ft_strlen(ex_code);
				x += 2;
		}
		else
		{
			str[y++] = cmd[x++];
		}
	}
	str[y] = '\0';
	return(free(ex_code), free(cmd), str);
}
int count_expantion_here(char *str)
{
	int x;
	int ndx;
	int count;

	x = 0;
	ndx = 0;
	count = 0;
	while (str[x])
	{
		if (str[x] == '<' && str[x + 1] == '<')
		{
			x += 3;
			while (str[x] && str[x] != ' ')
			{
				if (str[x] == '\'' || str[x] == '"')
					ndx++;
				x++;
			}
			if (ndx != 0)
				count++;
		}
		if (str[x])
			x++;
	}
	return (count);
}
 int cmd_expa_h1(char *str, t_ndx *ind)
{
	int hold;
	int grip;

	hold = ind->x;
	grip = 0;
	while (str[hold])
	{
		if (str[hold] == '<' && str[hold + 1] == '<')
		{
			grip = hold;
			hold += 3;
			while (str[hold] && str[hold] != ' ')
			{
				if (str[hold] == '\'' || str[hold] == '"')
					return (grip);
				hold++;
			}
		}
		if (str[hold])
			hold++;
	}
	return (-1);
}
char *cmd_expa(char *str, t_list *env, int *red)
{
	char	*cmd;
	
	t_ndx	xy = {0, 0, 0};
	cmd = cmd_alloctation(str, env);
	turn_back(str, 1);
	turn_here_do(str);
	turn_double(str, 1);
	
	while ((size_t)xy.x < ft_strlen(str))
	{
		if(str[xy.x] == '$')
		{
			if ((!ft_isalnum(str[xy.x + 1])) && str[xy.x + 1] != '_')
			{
				cmd[xy.y++] = str[xy.x++];
				continue;
			}
			handle_var_exp(str, env, cmd, &xy);
		}
		else if ((size_t)xy.x < ft_strlen(str))
		{
			if (xy.x == cmd_expa_h1(str, &xy))
			{
				cmd[xy.y++] = str[xy.x++];
				cmd[xy.y++] = str[xy.x++];
				cmd[xy.y++] = '<';
			}
			else 
				cmd[xy.y++] = str[xy.x++];
		}
	}	
	cmd[xy.y] = '\0';
	the_turns(cmd, 1);
	cmd = expand_ex_code(cmd, red);
	return(free(str), cmd);
}
