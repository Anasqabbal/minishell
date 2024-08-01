/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_1open_here_doc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/31 17:07:19 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/01 09:12:02 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	first_check(char **res, char *here_doc, char *lim, char **tmp)
{
	*res = readline(">");
	if (!(*res) || (!ft_strncmp(*res, lim, ft_strlen(*res))
			&& (ft_strlen(*res) == ft_strlen(lim))) || lim[0] == '\0')
	{
		if (!ttyname(0))
		{
			free(here_doc);
			g_sig = 1;
			if (open(ttyname(2), O_RDWR) == -1)
				return (-1);
			return (1);
		}
		return (2);
	}
	if (res[0][0] != '\0')
		add_history(*res);
	*res = add_new_line(res);
	if (!(*res))
		return (-1);
	return (*tmp = here_doc, 0);
}

static char	*last_check(char **here_doc, char *res, int r)
{
	signal(SIGINT, ft_handler);
	(void)r;
	if (!(*here_doc))
	{
		*here_doc = ft_strdup("");
		if (!(*here_doc))
			return (NULL);
	}
	free(res);
	return (*here_doc);
}

static int	go_to_expand(char **res, t_list **env, int *ret)
{
	int	j;

	if (!res || !(*res))
		return (0);
	*res = dollar_sign(*res, 0);
	*res = blurr_dollar_digit(*res, 0);
	*res = cmd_expa(*res, *env, ret);
	j = 0;
	while (res[0][j])
	{
		if (res[0][j] < 0)
			res[0][j] *= -1;
		j++;
	}
	return (0);
}

char	*read_from_here_doc(char **red, int i, t_list **env, int *ret)
{
	char	*here_doc;
	char	*tmp;
	char	*res;
	int		r;

	here_doc = NULL;
	tmp = NULL;
	signal(SIGINT, ft_handler_here);
	while (1 && red && red[i])
	{
		r = first_check(&res, here_doc, red[i + 1], &tmp);
		if (r == -1)
			return (NULL);
		else if (r == 1 || r == 2)
			break ;
		if (ft_strncmp(red[i], "<<<", 3) && ft_strlen(red[i]) != 3)
			go_to_expand(&res, env, ret);
		here_doc = my_strjoin(here_doc, res);
		if (!here_doc)
			return (free(tmp), free(res), NULL);
		free(res);
		free(tmp);
	}
	return (last_check(&here_doc, res, r));
}
