/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/15 11:47:33 by anqabbal          #+#    #+#             */
/*   Updated: 2024/08/05 13:08:26 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	exit_with(int ret, t_prs *p, t_exec *e, t_list *envp)
{
	ft_clear_exec(&e);
	ft_lstclear(&envp, free);
	clear_prs(&p);
	exit(ret);
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
	if ((ft_strlen(str) >= 20))
		return (ft_ex_error("exit: ", str, 255));
	while (str[i] >= 48 && str[i] <= 57)
	{
		res1 = res;
		while ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
			i++;
		res = res * 10 + (str[i++] - 48);
		if (((res < res1 && sign == 1))
			|| ((res < res1 && res > (LLONG_MIN) && sign == -1)))
			return (free(s), ft_ex_error("exit: ", str, 255));
	}
	return (to_free(s), res * sign);
}

int	a_while(t_exec *e, int i, int ind, char **res)
{
	int	j;

	if (calcul_args(res) > 1
		|| (calcul_args(e->cmd + 1) > 1 && calcul_args(res) > 1))
		return (ft_ex_error("exit: ", res[i], 255), to_free(res), 255);
	j = -1;
	while (res[i][++j])
	{
		if (ft_isdigit(res[i][j]) || res[i][0] == ' ')
			continue ;
		else if ((res[i][0] == '-' || res[i][0] == '+') && ind == 0)
			ind = 1;
		else
			return (ft_ex_error("exit: ", res[i], 255), to_free(res), 255);
	}
	return (0);
}

int	prepare_exit_cod(t_exec *e, t_prs *p, t_list *envp)
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
	if (res[0] == NULL)
		return (ft_ex_error("exit: ", res[0], 255),
			to_free(res), exit_with(255, p, e, envp), 1);
	while (res[i])
	{
		ret = a_while(e, i, ind, res);
		if (ret)
			exit_with(ret, p, e, envp);
		else if (!ret && res[i + 1])
			continue ;
		i++;
	}
	if (calcul_args(e->cmd + 1) > 1)
		return (to_free(res), ft_ex_error("exit: ", e->cmd[1], 1), 1);
	return (exit_with(atoi_ex(res[0], res), p, e, envp), 0);
}

unsigned char	ft_exit(t_exec *e, t_list **envp, t_prs **l)
{
	int	ret;

	(void)envp;
	ret = 0;
	if ((e->cmd[1]))
	{
		if (e->cmd[0][0] == '\0')
		{
			ret = ft_ex_error("exit: ", e->cmd[1], 255);
			exit_with(ret, *l, e, *envp);
		}
		ret = prepare_exit_cod(e, *l, *envp);
	}
	else
	{
		ret = e->ex;
		exit_with(ret, *l, e, *envp);
	}
	return (ret);
}
