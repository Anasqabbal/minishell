/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipping_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:43 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/31 20:07:18 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	blurr_dollar_digit_wh(char *str, char *cmd, int *y, int ndx)
{
	int	x;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] == '<' && str[x + 1] == '<' && ndx == 1)
		{
			the_three(str, cmd, y, &x);
			turn_back(str, 1);
			while (str[x] && str[x] != ' ')
			{
				if (str[x] < 0)
					cmd[(*y)++] = str[x++] * -1;
				else
					cmd[(*y)++] = str[x++];
			}
			turn_back(str, 1);
		}
		else if (str[x] == '$' && ft_isdigit(str[x + 1])
			&& !turn_dollar_2(str, x))
			x += 2;
		else
			cmd[(*y)++] = str[x++];
	}
}

char	*blurr_dollar_digit(char *str, int ndx)
{
	int		x;
	char	*cmd;
	int		y;

	x = 0;
	y = 0;
	cmd = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!cmd)
		return (free(cmd), NULL);
	blurr_dollar_digit_wh(str, cmd, &y, ndx);
	cmd[y] = '\0';
	return (free(str), cmd);
}

void	the_three_1(char *str, char *cmd, t_ndx_c *indi)
{
	cmd[indi->y++] = str[indi->x++];
	cmd[indi->y++] = str[indi->x++];
	cmd[indi->y++] = str[indi->x++];
}
// void	dollar_while_h1(char *str, char *cmd, t_ndx_c *indi)
// {
	
// }
void	dollar_while_h(char *str, char *cmd, t_ndx_c *indi)
{
	int hold;
	int count;
	int z;
	int ndx;

	ndx = 0;
	the_three_1(str, cmd, indi);
	turn_back(str, 1);
	// printf("**%s\n", str);
	while (str[indi->x])
	{
		if (str[indi->x] != ' ')
		{
			turn_back(str, 1);
			break ;
		}
		if (str[indi->x] == '$')
		{
			hold = indi->x;
			count = 0;
			while (str[hold] == '$')
			{
				count++;
				hold++;
			}
			if ((str[hold] == '"' || str[hold] == '\'') && !turn_dollar(str, hold - 1))
			{
				z = 0;
				if (count % 2 != 0)
				{
					indi->x++;
					while (z < count)
					{
						cmd[indi->y++] = str[indi->x++];
							z++;
						}
				} 
				else
				{
					while (z < count)
					{
						cmd[indi->y++] = str[indi->x++];
						z++;
					}
				}
			}
			else
				cmd[indi->y++] = str[indi->x++];
		}
		else
			cmd[indi->y++] = str[indi->x++];
	}
}
void dollar_while(char *str, char *cmd, t_ndx_c *indi, int ndx)
{
	int hold;
	int count;
	int z;
	
	while (str[indi->x])
	{
		if (str[indi->x] == '<' && str[indi->x + 1] == '<' && ndx == 1)
			dollar_while_h(str, cmd, indi);
		else if (str[indi->x] == '$')
		{
			hold = indi->x;
			count = 0;
			while (str[hold] == '$')
			{
				hold++;
				count++;
			}
			if ((str[hold] == '"' || str[hold] == '\'') && !turn_dollar(str, hold - 1))
			{
				z = 0;
				if (count % 2 != 0 )
				{
					indi->x++;
					while (z < count)
					{
						if (str[indi->x] == '$')
							str[indi->x] *= -1;
						cmd[indi->y++] = str[indi->x++];
						z++;
					}
				}
				else
				{
					while (z < count)
					{
						if (str[indi->x] == '$')
							str[indi->x] *= -1;
						cmd[indi->y++] = str[indi->x++];
						z++;
					}
				}
			}
			else
			{
				z = 0;
				if (count % 2 != 0)
				{
					while (z < (count - 1))
					{
						if (str[indi->x] == '$')
							str[indi->x] *= -1;
						cmd[indi->y++] = str[indi->x++];
						z++;
					}
					cmd[indi->y++] = str[indi->x++];
				}
				else
				{
					while (z < count)
					{
						if (str[indi->x] == '$')
							str[indi->x] *= -1;
						cmd[indi->y++] = str[indi->x++];
						z++;
					}
				}
			}
		}
		else
			cmd[indi->y++] = str[indi->x++];
	}
}
char *dollar_sign(char *str, int ndx)
{
    char	*cmd;
	t_ndx_c indi = (t_ndx_c){0, 0};
	
    cmd = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (!cmd) 
		return (free(cmd), NULL);
	dollar_while(str, cmd, &indi, ndx);
    cmd[indi.y] = '\0';
  	return (free(str), cmd);
}
