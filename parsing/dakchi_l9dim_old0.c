/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   Blen: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/16 14:14:22 blen zgtaib            #+#    #+#             */
/*   Updated: 2024/05/15 19:44:47 blen zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

// t_list	*ft_envdup(char **env)
// {
// 	int i;
// 	t_list *res;
// 	t_list *head;

// 	i = 0;
// 	head = NULL;
// 	while (env[i])
// 	{
// 		res = ft_lstnew(ft_strdup(env[i]));
// 		if (!res)
// 			return (NULL);
// 		ft_lstadd_back(&head, res);
// 		i++;
// 	}
// 	return (head);	
// }

void ft_strcpy(char *s1, char *s2)
{
	int x = 0;
	while ((size_t)x < ft_strlen(s2))
	{
		s1[x] = s2[x];
		x++;
	}
	s1[x] = '\0';
}
// void	ft_getenv_ours(char *str, t_list *env, char *path)
// {
// 	char	*tmp;
// 	int		f_l;

// 	tmp = ft_strchr(str, '=');
// 	if (!tmp)
// 		return ;
// 	f_l = ft_strlen(str) - ft_strlen(tmp) + 1;
// 	while (env)
// 	{
// 		if (!ft_strncmp(env->content, str, f_l))
// 		{
// 			free(env->content);
// 			env->content = ft_strdup(path);
// 		}
// 		env = env->next;
// 	}
// }
t_list	*ft_getenv(char *str, t_list *env)
{
	char	*tmp;
	int		f_l;

	tmp = ft_strchr(str, '=');
	if (!tmp)
		return (NULL);
	f_l = ft_strlen(str) - ft_strlen(tmp) + 1;
	while (env)
	{
		if (!ft_strncmp(env->content, str, f_l))
			return (env);
		env = env->next;
	}
	return (NULL);
}
void	free_it(char **arg, int count)
{
	int	i;

	i = 0;
	while (i < count)
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
t_prs *init_prs(void) 
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
int ft_isspace(char c)
{
	if (c == ' ' || (c >= 9 && c <= 13))
		return (1);
	return (0);
}
char *replacewihte_s(char *str)
{
	int x;
	int len;
	int is_space;

	x = 0;
	is_space = 0;
	len = 0;
	while (str[x] != '\0')
	{
		if (ft_isspace(str[x]))
		{ 
			if (!is_space)
			{
				str[len] = ' ';
				len++;
				is_space = 1;
			}
		}
		else
		{
			str[len] = str[x];
			len++;
			is_space = 0;
		}
		x++;
	}
	str[len] = '\0';
	return (str);
}

char *ft_syntax(char *stl)
{
	int x;
	int len;
	char *str;
	char hold;
	int ndx;

	len = ft_strlen(stl);
	x = 0;
	while ((stl[len - 1] == ' ' || (stl[len - 1] >= 9 && stl[len - 1] <= 13)) && len > 1)
		len--;	
  	if (stl[len - 1] == '|' || stl[len - 1] == '<' || stl[len - 1] == '>') 
        return(0);
	str = replacewihte_s(stl);	
	while (str[x] == ' ' || (str[x] > 9 && str[x] < 13))
		x++;	
	if (str[x] == '|')
        return(0);
	ndx = x;
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
				str[x] *= -1;
                x++;
            }
		}
		if(!ft_strncmp(&str[x], ">|", ft_strlen(">|")))
		{
			while (str[x + 2] == ' ' || (str[x + 2] >= 9 && str[x + 2] <= 13))
				x++;
			if(str[x + 2] == '>'|| str[x + 2] == '<')
			{
				free(str);
				return (NULL);
			}
		}
		if (!ft_strncmp(&str[x], "<< |", ft_strlen("<< |")) ||
            !ft_strncmp(&str[x], "<<|", ft_strlen("<<|")) ||
            !ft_strncmp(&str[x], ">>>", ft_strlen(">>>")) ||
            !ft_strncmp(&str[x], "<<<", ft_strlen("<<<")) ||
            !ft_strncmp(&str[x], "< |", ft_strlen("< |")) ||
            !ft_strncmp(&str[x], "<|", ft_strlen("<|")) ||
            !ft_strncmp(&str[x], "> |", ft_strlen("> |")) ||
            !ft_strncmp(&str[x], ">> |", ft_strlen(">> |")) ||
            !ft_strncmp(&str[x], ">>|", ft_strlen(">>|")) ||
            !ft_strncmp(&str[x], "| |", ft_strlen("| |")) ||
            !ft_strncmp(&str[x], "||", ft_strlen("||")) ||
            !ft_strncmp(&str[x], ">> >>", ft_strlen(">> >>")) ||
            !ft_strncmp(&str[x], "<< <<", ft_strlen("<< <<")) ||
            !ft_strncmp(&str[x], "< <", ft_strlen("< <")) ||
            !ft_strncmp(&str[x], "> >", ft_strlen("> >")) ||
            !ft_strncmp(&str[x], "< >", ft_strlen("< >")) ||
            !ft_strncmp(&str[x], "<>", ft_strlen("<>")) ||
            !ft_strncmp(&str[x], "> <", ft_strlen("> <")) ||
            !ft_strncmp(&str[x], "><", ft_strlen("><"))) 
		{
            free(str);
            return NULL;
        }
			x++;
	}
	return (str);
}

int check_qts(char *input, int *count, int *qts)
{
	int x;
	char hold;

	x = 0;
	while ((size_t)x < ft_strlen(input))
	{
		if (input[x] == '"' || input[x] == '\'')
		{
			(*qts)++;
			hold = input[x];
			x++;
			if (input[x] == '\0')
				break ;
			while ((size_t)x < ft_strlen(input))
			{
				if (input[x] == hold)
				{
					(*qts)++;
					break ;
				}
				x++;
			}
		}
		if(input[x] == '|' || input[x] == '>' || input[x] == '<')
    	{
        	if ((input[x] == '>' && input[x + 1] == '>') || (input[x] == '<' && input[x + 1] == '<'))
        	{
        		x++;
        		x++;
       		}
        	(*count)++;
   	 	}
		x++;
	}
	if ((*qts) % 2 != 0)
		return(0);
	return (1);
}

char *put_spaces(char *cmd, int count) 
{
    int x;
    char *str;
	int inside_quotes;
	char current_quote;
	int y; 

    str= (char *)malloc((ft_strlen(cmd) + (count * 2)+ 1) * sizeof(char));
    if (!str) 
	{
        free(cmd);
        return NULL;
    }
	y = 0;
    inside_quotes = 0;
    current_quote = '\0';
	x = 0;
    while (cmd[x] != '\0')
	{
		if (cmd[x] == '|')
		{
			if (y > 0 && str[y - 1] != ' ') 
                	str[y++] = ' ';
            str[y++] = cmd[x];
	    	if (cmd[x + 1] != ' ' && cmd[x + 1] != '\0')
                str[y++] = ' ';
		}
		else if (cmd[x] == '>' || cmd[x] == '<')
		{
			if (cmd[x + 1] == '>' || cmd[x + 1] == '<')
			{	
				if (y > 0 && str[y - 1] != ' ') 
                	str[y++] = ' ';
				str[y++] = cmd[x++];
				str[y++] = cmd[x];
				if (cmd[x + 1] != ' ' && cmd[x + 1] != '\0')
                str[y++] = ' ';
			}
			else
			{
				if (y > 0 && str[y - 1] != ' ') 
                	str[y++] = ' ';
            	str[y++] = cmd[x];
	    		if (cmd[x + 1] != ' ' && cmd[x + 1] != '\0')
                str[y++] = ' ';
			}
		}
		else 
            str[y++] = cmd[x];
        x++;
    }
    str[y] = '\0';
    free(cmd);
    return (str);
}
void turn_back(char *str, int ndx)
{
	int x;
	char hold;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '"' || str[x] == '\'')
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
                x++;
            }
		}
		x++;
	}
}

void add_to_struct(char ***array, char *element)
{
	int count = 0;
	int i = 0;
    while (*array && (*array)[count])
        count++;
    char **new_array = (char **)malloc((count + 2) * sizeof(char *));
    while (i < count)
	{
        new_array[i] = (*array)[i];
		i++;
	}
    new_array[count] = ft_strdup(element);
    new_array[count + 1] = NULL;
    free(*array);
    *array = new_array;
}
void parse_command(char **tokens, t_prs *node)
{
	int y;
  	
	if (!tokens[0])
        return;
	y = 1;
	turn_back(tokens[0], 1);
	if (tokens[0][0] != '<' && tokens[0][0] != '>')
		node->cmd = ft_strdup(tokens[0]);
	while (tokens[y] != NULL)
	{	
		turn_back(tokens[y], 1);
		if (tokens[y][0] == '-')
			add_to_struct(&node->opts, tokens[y]);
		else if (tokens[y][0] == '"' && tokens[y][1] == '-')
			add_to_struct(&node->opts, tokens[y]);
		y++;
	}
}
int arg_count(char **str)
{
	int x;

	x = 0;
	while (str[x] != NULL)
		x++;
	return (x);
}

void parse_redirections(char **tokens, t_prs *node)
{
    
	int len = arg_count(tokens);
	int ndx = 1;
	int y;
	if (tokens[0][0] != '>' && tokens[0][0] != '<')
		y = 1; 
	else
		y = 0;
	
	while (y < len)
    {
        if (tokens[y][0] == '>')
        {
			if (tokens[0][0] == '>' && ndx == 1)
			{
				add_to_struct(&node->red, tokens[y]);
				add_to_struct(&node->red, tokens[y + 1]);
				if (tokens[y + 2][0] != '>' && tokens[y + 2][0] != '<' && tokens[y + 2] != NULL)
					node->cmd = tokens[y + 2];
				ndx = 0;
			}
			else 
			{
            	add_to_struct(&node->red, tokens[y]);
        		add_to_struct(&node->red, tokens[y + 1]);
			}
		
       	}
        else if (tokens[y][0] == '<')
        {
            if (tokens[0][0] == '<' && ndx == 1)
			{
				add_to_struct(&node->red, tokens[y]);
				add_to_struct(&node->red, tokens[y + 1]);
				if (tokens[y + 2][0] != '>' && tokens[y + 2][0] != '<' && tokens[y + 2] != NULL)
					node->cmd = tokens[y + 2];
				ndx = 0;
			}
			else 
			{
            	add_to_struct(&node->red, tokens[y]);
        		add_to_struct(&node->red, tokens[y + 1]);
			}
			
        }
       	else if ((tokens[y][0] != '>' && tokens[y][0] != '<' && tokens[y][0] != '-') && (tokens[y - 1][0] != '<'  && tokens[y - 1][0] != '>') && (tokens[y][0] == '"' && tokens[y][1] != '-'))
        {
            add_to_struct(&node->arg, tokens[y]);
        }
		y++;
	}
}

char *expand_variable(char *str, t_list *env, int *ndx)
{
	char *hold;
	t_list *expa;
	int len;

	hold = ft_strjoin(str, "=");
	if(!hold)
		return(free(str), NULL);
	len = ft_strlen(hold);
	expa = ft_getenv(hold, env);
	if (!expa)
	{
		(*ndx) = 1;
		return (free(hold), NULL);
	}	
	hold = ft_strdup(expa->content);
	return (hold + len);
}
char *extract_virable(char *str, int *var_len)
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
int calaculate_expan_len(char *str, t_list *env)
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
		else if ((size_t) x < ft_strlen(str))
				cmd[y++] = str[x++];
	}
	cmd[y] = '\0';
	return (free(str), cmd);
}
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
                x++;
            }
		}
		x++;
	}
}
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
t_prs *pipe_split(char *cmd, int opp, int qts, t_list *env)
{	
	char **splt_pip;
	char *final;
	t_prs *head = NULL;
	t_prs *current = NULL;
	char *com;
	char *cmd1;
	int y;

	final = put_spaces(cmd, opp + qts);
	turn_back(final, 1);
	cmd1 = dollar_sign(final);
	printf("//%s\n", cmd1);
	com = cmd_expa(cmd1, env);
	printf("**%s\n", com);
	turn_back(com, 1);
	splt_pip = ft_split(com, '|');
	y = 0;
	while (splt_pip[y] != NULL)
	{
		t_prs *new = init_prs();
		if (!new)
		{
			free(com);
			return (NULL);
		}
		char **splt_space = ft_split(splt_pip[y], ' ');
		parse_command(splt_space, new);
		parse_redirections(splt_space, new);	
        if (head == NULL) {
            head = new;
        } else {
            current->next = new;
        }
        current = new;
		y++;	
	}
	free(com);
	return (head);
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
		return (*ret = 258 ,0);
	cmd = ft_syntax(raw);
	if (!cmd)
		return (*ret = 258 ,0);
	if(!check_qts(cmd, &opp, &qts))
		return (*ret = 258 ,0);
	
	(*node) = pipe_split(cmd, opp, qts, env);
	return (1);
}
// int main(int argc, char **argv,  char **env)
// {
// 	char *input;
// 	t_list *envi;
// 	t_prs *node;

// 	(void)argc;
// 	(void)argv;
// 	node = NULL;
// 	envi = ft_envdup(env);		
// 	if(!envi)
// 		return(1);
// 	while (1)
// 	{
// 		input = readline("minishell$ = ");
// 		// int x = 0;
// 		if (input == NULL)
// 			return (1);
// 		if (input[0] != '\0')
// 			add_history(input);
// 		if (!check_syntax(input, envi, &node))
// 			write(2, "syntax error\n", 13);
// 		printf("cmd = %s\n", node->cmd);
// 		printf("opts = %s\n", node->opts[0]);
// 		printf("arg = %s\n", node->arg[0]);
// 		// printf("arg = %s\n", node->arg[1]);
// 		// printf("red = %s\n", node->red[0]);
// 		// printf("file = %s\n", node->red[1]);
// 		// printf("red =%s\n", node->red[2]);
// 		// printf("file = %s\n", node->red[3]);
// 		free(input);
// 	}
// }
