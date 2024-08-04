/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_er_msg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/01 20:03:51 by zgtaib            #+#    #+#             */
/*   Updated: 2024/08/04 12:49:17 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	error_msg(char c)
{
	if (c == '|')
		write(2, "minishell: syntax error snear unexpected token `|'\n", 52);
	else if (c == '>')
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 56);
	else if (c == '<')
		write(2,
			"minishell: syntax error near unexpected token `newline'\n", 56);
}

static int	error_msg1h(char *str, int x)
{
	if (!ft_strncmp(&str[x], "<< |", ft_strlen("<< |"))
		|| !ft_strncmp(&str[x], "<<|", ft_strlen("<<|"))
		|| !ft_strncmp(&str[x], "< |", ft_strlen("< |"))
		|| !ft_strncmp(&str[x], "<|", ft_strlen("<|"))
		|| !ft_strncmp(&str[x], "> |", ft_strlen("> |"))
		|| !ft_strncmp(&str[x], ">> |", ft_strlen(">> |"))
		|| !ft_strncmp(&str[x], ">>|", ft_strlen(">>|"))
		|| !ft_strncmp(&str[x], "| |", ft_strlen("| |"))
		|| !ft_strncmp(&str[x], ">|", ft_strlen(">|")))
	{
		write(2, "minishell: syntax error near unexpected token `|'\n", 50);
		return (0);
	}
	else if (!ft_strncmp(&str[x], ">>>>", ft_strlen(">>>>"))
		|| !ft_strncmp(&str[x], ">> >>", ft_strlen(">> >>"))
		|| !ft_strncmp(&str[x], "< >>", ft_strlen("< >>"))
		|| !ft_strncmp(&str[x], "<< >>", ft_strlen("<< >>"))
		|| !ft_strncmp(&str[x], "<<>>", ft_strlen("<<>>"))
		|| !ft_strncmp(&str[x], "<>>", ft_strlen("<>>"))
		|| !ft_strncmp(&str[x], "> >>", ft_strlen("> >>")))
	{
		write(2, "minishell: syntax error near unexpected token `>>'\n", 52);
		return (0);
	}
	return (1);
}

static int	error_msg1h1(char *str, int x)
{
	if (!ft_strncmp(&str[x], ">>>", ft_strlen(">>>"))
		|| !ft_strncmp(&str[x], ">> >", ft_strlen(">> >")))
	{
		write(2, "minishell: syntax error near unexpected token `>'\n", 51);
		return (0);
	}
	else if (!ft_strncmp(&str[x], "<<<<", ft_strlen("<<<<"))
		|| !ft_strncmp(&str[x], "<< <<", ft_strlen("<< <<"))
		|| !ft_strncmp(&str[x], "><<", ft_strlen("><<"))
		|| !ft_strncmp(&str[x], ">> <<", ft_strlen(">> <<"))
		|| !ft_strncmp(&str[x], ">><<", ft_strlen(">><<"))
		|| !ft_strncmp(&str[x], "> <<", ft_strlen("> <<"))
		|| !ft_strncmp(&str[x], "< <<", ft_strlen("< <<")))
	{
		write(2, "minishell: syntax error near unexpected token `<<'\n", 51);
		return (0);
	}
	else if (!ft_strncmp(&str[x], "<<<", ft_strlen("<<<"))
		|| !ft_strncmp(&str[x], "<< <", ft_strlen("<< <")))
	{
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
		return (0);
	}
	return (1);
}

static int	error_msg1h2(char *str, int x)
{
	if (!ft_strncmp(&str[x], "< <", ft_strlen("< <"))
		|| !ft_strncmp(&str[x], "> <", ft_strlen("> <"))
		|| !ft_strncmp(&str[x], "><", ft_strlen("><"))
		|| !ft_strncmp(&str[x], ">> <", ft_strlen(">> <"))
		|| !ft_strncmp(&str[x], ">><", ft_strlen(">><")))
	{
		write(2, "minishell: syntax error near unexpected token `<'\n", 51);
		return (0);
	}
	else if (!ft_strncmp(&str[x], "> >", ft_strlen("> >"))
		|| !ft_strncmp(&str[x], "<>", ft_strlen("<>"))
		|| !ft_strncmp(&str[x], "< >", ft_strlen("< >"))
		|| !ft_strncmp(&str[x], "<< >", ft_strlen("<< >"))
		|| !ft_strncmp(&str[x], "<<>", ft_strlen("<<>")))
	{
		write(2, "minishell: syntax error near unexpected token `>'\n", 51);
		return (0);
	}
	else if (!ft_strncmp(&str[x], "&&", ft_strlen("&&")))
	{
		write(2, "minishell: syntax error near unexpected token `&&'\n", 52);
		return (0);
	}
	return (1);
}

int	error_msg1(char *str, int x)
{
	if (!error_msg1h(str, x))
		return (0);
	else if (!error_msg1h1(str, x))
		return (0);
	else if (!error_msg1h2(str, x))
		return (0);
	else if (!error_msg1h3(str, x))
		return (0);
	return (1);
}
