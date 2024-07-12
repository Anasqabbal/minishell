/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:47:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/07/03 15:57:39 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	ft_ex_error(char *from, char *nam, int rt)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(from, 2);
	if (rt == 255)
	{
		ft_putstr_fd(nam, 2);
		ft_putendl_fd(": numeric argument required", 2);
	}
	else if (rt == 1)
		ft_putendl_fd("too many arguments", 2);
	return (rt);
}

static int	atoi_ex(char *str, char **s)
{
	int				i;
	int				sign;
	long long int	res;
	long long int	res1;

	sign = 1;
	i = 0;
	res = 0;
	if (str[0] == '+' || str[0] == '-')
		i = 1;
	if (str[0] == '-')
		sign = -1;
	while (str[i] >= 48 && str[i] <= 57)
	{
		res1 = res;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		res = res * 10 + (str[i++] - 48);
		if ((res < res1 && sign == 1)
			|| ((res < res1 && res > (LLONG_MIN) && sign == -1)))
			return (free(s), exit (ft_ex_error("exit: ", str, 255)), 1);
	}
	to_free(s);
	return (res * sign);
}

int	a_while(t_exec *e, int i, int ind, char **res)
{
	int	j;

	if (calcul_args(res) > 1
		|| (calcul_args(e->cmd + 1) > 1 && calcul_args(res) > 1))
	{
		to_free(res);
		exit (ft_ex_error("exit: ", e->cmd[i], 255));
	}
	j = -1;
	while (res[i][++j])
	{
		if (ft_isdigit(res[i][j]) || res[i][0] == ' ')
			continue ;
		else if ((res[i][0] == '-' || res[i][0] == '+') && ind == 0)
			ind = 1;
		else
		{
			to_free(res);
			exit (ft_ex_error("exit: ", res[i], 255));
		}
	}
	return (0);
}

int	prepare_exit_cod(t_exec *e)
{
	char	**res;
	int		i;
	int		ind;
	int		ret;

	i = 0;
	ind = 0;
	res = ft_split(e->cmd[1], ' ');
	if (!res)
		return (1);
	if (res[0] == NULL && calcul_args(e->cmd) == 1)
		return (to_free(res), ft_ex_error("exit: ", res[0], 2));
	while (res[i])
	{
		ret = a_while(e, i, ind, res);
		if (!ret && res[i + 1])
			continue ;
		i++;
	}
	if (calcul_args(e->cmd + 1) > 1)
		return (to_free(res), ft_ex_error("exit: ", e->cmd[1], 1), 1);
	ft_clear_exec(&e);
	return (exit (atoi_ex(res[0], res)), 0);
}

unsigned char	ft_exit(t_exec *e, t_list **envp, t_prs **l)
{
	int	ret;

	(void)envp;
	ret = 0;
	if ((e->cmd[1]))
		ret = prepare_exit_cod(e);
	else
	{
		(void) l;
		ret = e->ex;
		ft_clear_exec(&e);
		// clear_prs(l);
		ft_lstclear(envp, free);
		exit(ret);
	}
	return (ret);
}
