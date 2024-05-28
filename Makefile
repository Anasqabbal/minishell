# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: anqabbal <anqabbal@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/04/16 16:28:17 by zgtaib            #+#    #+#              #
#    Updated: 2024/05/28 10:19:58 by anqabbal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CC = cc
CFLAGS = -Wall -Wextra -Werror
INCLUDES = minishell.h ./libft/libft.h
LIBFT = libft/libft.a
F = -fsanitize=address -g

BUILTINS = execution/builtins/check_variable.c execution/builtins/env.c\
			execution/builtins/export.c execution/builtins/sort_with_ascii.c execution/builtins/unset.c execution/builtins/exit.c
EXECUTION = execution/env_utils.c execution/ft_additional_lst.c  execution/prepare_path.c execution/prepare_cmd.c $(BUILTINS) ft_errors.c execution/additional_ft.c\
execution/start_exec_00.c execution/additional_ft2.c execution/ft_1open_in_files.c execution/ft_1open_out_files.c execution/start_exec_01_cmds.c

PARSING = parsing/parsing.c

SRC = minishell.c $(EXECUTION) $(PARSING)

OBJ = $(SRC:.c=.o)

all: lib $(NAME)

lib :
	$(MAKE) -C ./libft

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) -lreadline -o $@ $(OBJ) $(LIBFT) $(F)

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