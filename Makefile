# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mgiovana <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/02 15:17:45 by mgiovana          #+#    #+#              #
#    Updated: 2023/11/02 15:17:48 by mgiovana         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
SRC = 	main.c init.c init1.c signal.c utils.c utils1.c  lexer.c \
		cmdsystem.c parsing.c heredoc.c fd_redir.c sys_utils.c \
		manage_redir1.c manage_redir.c exe.c pipe.c fork.c builtin.c\
		child_exe.c buildins.c buildins2.c export.c export1.c export2.c \
		export3.c sys_cmd.c
OBJ = $(SRC:.c=.o)
CC = gcc
RM = rm -f
CFLAGS = -Wall -Wextra -Werror -g
LIBFT = ./src/libft/libft.a
GNL = ./src/GNL/GNL.a
PRINTF = ./src/Printf/libftprintf.a


all: lib printf gnl $(NAME)

lib:
	make -s -C src/libft

printf:
	make -s -C src/Printf
        
gnl:
	make -s -C src/GNL
	
$(NAME): $(OBJ)
	@echo "\033[32mCompiling $(NAME)"
	@gcc $(CFLAGS) $(OBJ) $(LIBFT) $(PRINTF) $(GNL) -lreadline -o $(NAME)
	@echo "Compiled\033[0;37m"

clean:
	@echo "\033[0;31mCleaning objects"
	@rm -rf $(OBJ)
	@make clean -s -C src/libft
	@make clean -s -C src/Printf
	@make clean -s -C src/GNL

fclean: clean
	@echo "\033[0;31mRemoving $(NAME)\033[0;37m"
	@rm -rf $(NAME)
	@make fclean -s -C src/libft
	@make fclean -s -C src/Printf
	@make fclean -s -C src/GNL

re: fclean all

.SILENT: $(OBJ) lib printf gnl
