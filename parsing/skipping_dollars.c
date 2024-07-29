/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipping_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zgtaib <zgtaib@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:43 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/28 17:05:38 by zgtaib           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int turn_dollar_2(char *str, int y)
{
	int x;
	char hold;
	int ho;

	x = 0;
	while (str[x] != '\0')
	{
		if (str[x] == '\'')
        {
          	hold = str[x];
			ho = x;
            x++;
			if (str[x] == '\0')
				break ;
           	while (str[x] != '\0')
            {
				if (str[x] == hold)
				{
					if (str[y] == '$' && y > ho && y < x)
						return (1);
					break;
				}
                x++;
            }
		}
		x++;
	}
	return (0);
}
void blurr_dollar(char *str)
{
	int x;
	
	x = 0;
	while (str[x])
	{
		if (str[x] == '$' && ft_isdigit(str[x + 1]))
			str[x] *= -1;
		x++;
	}
}
void blurr_dollar_digit_wh(char *str, char *cmd, int *y, int ndx)
{
	int x;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] == '<' && str[x + 1] == '<' && ndx == 1)
		{	
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
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
		else if (str[x] == '$' && ft_isdigit(str[x + 1]) && !turn_dollar_2(str, x))
			x += 2;
		else 
			cmd[(*y)++] = str[x++];
	}
}
char *blurr_dollar_digit(char *str, int ndx)
{
	int x;
	char *cmd;
	int y;
	
	x = 0;
	y = 0;
	cmd = malloc((ft_strlen(str) + 1) * sizeof(char));
	if (!cmd)
	{
		free(str);
		exit(1);
	}
	blurr_dollar_digit_wh(str, cmd, &y, ndx);
	cmd[y] = '\0';
	return (free(str), cmd);
}
void dollar_while(char *str, char *cmd, int *y, int ndx)
{
	int x;
	int hold;
	int count;
	int z;

	x = 0;
	
	while (str[x])
	{
		if (str[x] == '<' && str[x + 1] == '<' && ndx == 1)
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			turn_back(str, 1);	
			while (str[x] && str[x] != ' ')
			{
				if (str[x] == '$')
				{
					hold = x;
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
							x++;
							while (z < count)
							{
								cmd[(*y)++] = str[x++];
								z++;
							}
						} 
						else
						{
							while (z < count)
							{
								cmd[(*y)++] = str[x++];
								z++;
							}
						}
						turn_back(str, 1);
					}
					else
					{
						while (str[x] && str[x] != ' ')
							cmd[(*y)++] = str[x++];
					}
				}
				else
					cmd[(*y)++] = str[x++];
			}
		}
		else if (str[x] == '$')
		{
			hold = x;
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
					x++;
					while (z < count)
					{
						if (str[x] == '$')
							str[x] *= -1;
						cmd[(*y)++] = str[x++];
						z++;
					}
				}
				else
				{
					while (z < count)
					{
						if (str[x] == '$')
							str[x] *= -1;
						cmd[(*y)++] = str[x++];
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
						if (str[x] == '$')
							str[x] *= -1;
						cmd[(*y)++] = str[x++];
						z++;
					}
					cmd[(*y)++] = str[x++];
				}
				else
				{
					while (z < count)
					{
						if (str[x] == '$')
							str[x] *= -1;
						cmd[(*y)++] = str[x++];
						z++;
					}
				}
			}
		}
		else
			cmd[(*y)++] = str[x++];
	}
}
char *dollar_sign(char *str, int ndx)
{
    char *cmd;
    int y;

    y = 0;
    cmd = (char *)malloc((strlen(str) + 1) * sizeof(char));
    if (!cmd) 
	{
        free(str);
        exit(1);
    }
	dollar_while(str, cmd, &y, ndx);
    cmd[y] = '\0';
  	return (free(str), cmd);
}