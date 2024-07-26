/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   skipping_dollars.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 16:31:43 by zgtaib            #+#    #+#             */
/*   Updated: 2024/07/26 12:37:01 by anqabbal         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


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
void blurr_dollar_digit_wh(char *str, char *cmd, int *y)
{
	int x;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] == '>' && str[x + 1] == '>' && str[x + 3] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			if (ft_isdigit(str[x + 1]) && str[x + 2] != '\0' && str[x + 2] != ' ' )
				x += 2;
			else 
			{
				while (str[x] && str[x] != ' ')
					cmd[(*y)++] = str[x++];
			}
		}
		else if ( str[x] && ((str[x] == '<' && str[x + 1] != '<') || (str[x] == '>' && str[x + 1] != '>')) && str[x + 2] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			if (ft_isdigit(str[x + 1]) && str[x + 2] != '\0' && str[x + 2] != ' ')
				x += 2;
			else 
			{
				while (str[x] && str[x] != ' ')
					cmd[(*y)++] = str[x++];
			}
		}
		else if (str[x] && str[x] == '<' && str[x + 1] == '<' && str[x + 3] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			while (str[x] && str[x] != ' ')
				cmd[(*y)++] = str[x++];
		}
		else if (str[x] == '$' && ft_isdigit(str[x + 1]))
			x += 2;
		else 
			cmd[(*y)++] = str[x++];
	}
}
char *blurr_dollar_digit(char *str)
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
	blurr_dollar_digit_wh(str, cmd, &y);
	cmd[y] = '\0';
	return (free(str), cmd);
}

int count_dollar(char *str)
{
    int x;
    int count;

    x = 0;
    count = 0;
    while (str[x])
    {
          if (str[x] == '$')
            {
                while (str[x] == '$')
                {
                    count++;
                    x++;
                }
                if (str[x] == '"' || str[x] == '\'')
                {
					count++;
                    char quote_char = str[x];
                    x++;
                    while (str[x] && str[x] != quote_char)
                    {
                        if (str[x] == '$')
                        {
                            count++;
                        }
                        x++;
                    }
                    if (str[x] == quote_char)
                    {
						count++;
                        x++;
                    }
                }
            }
            else
            {
              while(str[x])
                x++;
            }
        }
        return (count);
    }


static void dollar_while(char *str, char *cmd, int *y)
{
	int x;
	// int count;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] == '>' && str[x + 1] == '>' && str[x + 3] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
		
				int dollar_count = count_dollar(&str[x]);	
				if (dollar_count % 2 != 0)
				{
					x += dollar_count;
					cmd[(*y)++] = '$';
				}
				else
				{
					if (ft_isalnum(str[x + dollar_count]))
						x += dollar_count; 
					else 
					{
						while (x < dollar_count)
						{
							if (str[x] == '$')
								str[x] *= -1;
							cmd[(*y)++] = str[x++];
						}
					}
				}
		}
		else if ( str[x] && ((str[x] == '<' && str[x + 1] != '<') || (str[x] == '>' && str[x + 1] != '>')) && str[x + 2] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
				int dollar_count = count_dollar(&str[x]);	
				if (dollar_count % 2 != 0)
				{
					x += dollar_count;
					cmd[(*y)++] = '$';
				}
				else
				{
					if (ft_isalnum(str[x + dollar_count]))
						x += dollar_count; 
					else 
					{
						while (x < dollar_count)
						{
							if (str[x] == '$')
								str[x] *= -1;
							cmd[(*y)++] = str[x++];
						}
					}
				}
		}
		else if (str[x] && str[x] == '<' && str[x + 1] == '<' && str[x + 3] == '$' )
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			int hold = x;
			int count = 0;
			while (str[hold] == '$')
			{
				count++;
				hold++;
			}
			if (str[hold] == '"' || str[hold] == '\'')
			{
				if (count % 2 != 0)
				{
					x++;
					while (str[x] && str[x] != ' ')
						cmd[(*y)++] = str[x++];

				} 
				else
				{
					while (str[x] && str[x] != ' ')
						cmd[(*y)++] = str[x++];
				}
			}
			else
			{
				while (str[x] && str[x] != ' ')
					cmd[(*y)++] = str[x++];
			}
		}
		else if (str[x] == '$')
		{
			int hold = x;
			int count = 0;
			while (str[hold] == '$')
			{
				hold++;
				count++;
			}
			if ((str[hold] == '"' || str[hold] == '\'') && !turn_dollar(str, hold - 1))
			{
			 	x = hold;
				cmd[(*y)++] = str[x++];
			}
			else 
			{
				if (count % 2 != 0)
				{
					x = hold;
					cmd[(*y)++] = '$';
				}
				else
				{
					int z = 0;
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
		// if(str[x])
		// 	x++;
}
char *dollar_sign(char *str)
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
	dollar_while(str, cmd, &y);
    cmd[y] = '\0';
  	return (free(str), cmd);
}

void dollar_skipping_while(char *str, char *cmd, int *y)
{
	int x;
	int count;

	x = 0;
	while (str[x])
	{
		if (str[x] && str[x] == '>' && str[x + 1] == '>' && str[x + 3] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			while (str[x] && str[x] != ' ')
				cmd[(*y)++] = str[x++];
		}
		else if ( str[x] && ((str[x] == '<' && str[x + 1] != '<') || (str[x] == '>' && str[x + 1] != '>')) && str[x + 2] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			while (str[x] && str[x] != ' ')
				cmd[(*y)++] = str[x++];
		}
		else if (str[x] && str[x] == '<' && str[x + 1] == '<' && str[x + 3] == '$')
		{
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			cmd[(*y)++] = str[x++];
			while (str[x] && str[x] != ' ')
				cmd[(*y)++] = str[x++];
		}
		else if (str[x] == '$')
		{
			count = 0;
			while (str[x] && str[x] =='$')
			{
				count++;
				x++;
			}
			if (count % 2 != 0)
				cmd[(*y)++] = '$';
		}
		else 
			cmd[(*y)++] = str[x++];
	}
}
char *dollar_skipping(char *str)
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
	dollar_skipping_while(str, cmd, &y);
	cmd[y] = '\0';
  	return (free(str), cmd);
}