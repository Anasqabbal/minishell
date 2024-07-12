# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 16:28:17 by zgtaib            #+#    #+#              #
#    Updated: 2024/07/12 14:44:07 by anqabbal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

F = -g -fsanitize=address
NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror $F
INCLUDES = minishell.h ./libft/libft.h
LIBFT = libft/libft.a

BUILTINS = execution/builtins/check_variable.c execution/builtins/env.c\
			execution/builtins/export.c execution/builtins/sort_with_ascii.c\
			execution/builtins/unset.c execution/builtins/exit.c\
			execution/builtins/echo.c execution/builtins/cd_utils.c\
			execution/builtins/pwd.c execution/builtins/cd.c
EXECUTION = execution/env_utils.c execution/ft_additional_lst.c  execution/prepare_path.c execution/prepare_cmd.c execution/additional_ft.c\
execution/start_exec_00.c execution/additional_ft2.c execution/ft_1open_in_files.c execution/ft_1open_out_files.c execution/start_exec_01_cmds.c\
execution/exec_functions.c  execution/start_exec_02_blts.c execution/ft_errors.c $(BUILTINS)

PARSING = parsing/ft_syntax.c\
	parsing/ft_env.c\
	parsing/ft_syntax_helper.c\
	parsing/ft_check_qts.c\
	parsing/ft_utils.c\
	parsing/ft_expantion.c\
	parsing/ft_split_cmd_h.c\
	parsing/ft_split_cmd.c\
	parsing/ft_utils_1.c\
	parsing/ft_parsing.c
	# parsing/dakchi_l9dim.c
	
	

SRC = minishell.c $(EXECUTION) $(PARSING)

OBJ = $(SRC:.c=.o)

all: lib $(NAME)

lib :
	$(MAKE) -C ./libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline -o $@ $(OBJ) $(LIBFT)

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)
	$(MAKE) -C ./libft $@

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C ./libft $@

re: fclean all

.PHONY: clean