# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akhastaf <akhastaf@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/12 17:27:32 by akhastaf          #+#    #+#              #
#    Updated: 2021/04/28 16:57:46 by akhastaf         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C = gcc
FLAGS = -Wall -Wextra -Werror
NAME = minishell
D = -g
SRC = ./srcs/*/*.c
OBJ = minishell

all: $(NAME)

$(NAME):
	@$(C) -g -o $(NAME) main.c $(SRC) -ltermcap

debug:
	@$(C) -g -o $(NAME) main.c $(SRC) -ltermcap -fsanitize=address 

clean:
	@rm -f $(NAME)

fclean: clean
		@rm -f $(NAME)

re: fclean all

.PHONY: re fclean clean all