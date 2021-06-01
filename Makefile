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

SRC = ./srcs/builtins/cd.c \
		./srcs/builtins/echo.c \
		./srcs/builtins/env.c \
		./srcs/builtins/exit.c \
		./srcs/builtins/export.c \
		./srcs/builtins/ft_isbuiltins.c \
		./srcs/builtins/init_export.c \
		./srcs/builtins/pwd.c \
		./srcs/builtins/unset.c \
		./srcs/env/ft_checkenv.c \
		./srcs/env/ft_getenv.c \
		./srcs/env/ft_getpath.c \
		./srcs/env/ft_set_lstcmd.c \
		./srcs/env/ft_set_pwd.c \
		./srcs/env/increment_shlvl.c \
		./srcs/errors/check.c \
		./srcs/errors/check_forbiden.c \
		./srcs/errors/count_doubleq.c \
		./srcs/errors/count_singleq.c \
		./srcs/execution/check_execute_errors.c \
		./srcs/execution/execute.c \
		./srcs/execution/execute_builtins.c \
		./srcs/execution/magic_box.c \
		./srcs/gnl/history.c \
		./srcs/gnl/readline.c \
		./srcs/gnl/setup_term.c \
		./srcs/gnl/signals.c \
		./srcs/minishell/minishell.c \
		./srcs/parser/count_backslash.c \
		./srcs/parser/ft_putbackslash.c \
		./srcs/parser/ft_refactor_line.c \
		./srcs/parser/ft_strremove.c \
		./srcs/parser/ft_tilde.c \
		./srcs/parser/init_pipeline.c \
		./srcs/parser/process.c \
		./srcs/pipe/pipe.c \
		./srcs/redirections/ft_getword.c \
		./srcs/redirections/get_options.c \
		./srcs/redirections/get_redirection.c \
		./srcs/redirections/remove_red.c \
		./srcs/redirections/setup_redirection.c \
		./srcs/utils/ft_argcmp.c \
		./srcs/utils/ft_argmap.c \
		./srcs/utils/ft_argprint.c \
		./srcs/utils/ft_argsize.c \
		./srcs/utils/ft_argtrim.c \
		./srcs/utils/ft_atoi.c \
		./srcs/utils/ft_atol.c \
		./srcs/utils/ft_count_space.c \
		./srcs/utils/ft_dealocate.c \
		./srcs/utils/ft_delete_arg.c \
		./srcs/utils/ft_free.c \
		./srcs/utils/ft_is_empty.c \
		./srcs/utils/ft_isalnum.c \
		./srcs/utils/ft_is_space.c \
		./srcs/utils/ft_isdigit.c \
		./srcs/utils/ft_itoa.c \
		./srcs/utils/ft_memcmp.c \
		./srcs/utils/ft_memcpy.c \
		./srcs/utils/ft_memdel.c \
		./srcs/utils/ft_putendl_fd.c \
		./srcs/utils/ft_puterror.c \
		./srcs/utils/ft_putstr.c \
		./srcs/utils/ft_putstr_fd.c \
		./srcs/utils/ft_quotes.c \
		./srcs/utils/ft_skip_space.c \
		./srcs/utils/ft_split.c \
		./srcs/utils/ft_strappend.c \
		./srcs/utils/ft_strchr.c \
		./srcs/utils/ft_strchrn.c \
		./srcs/utils/ft_strcmp.c \
		./srcs/utils/ft_strdup.c \
		./srcs/utils/ft_strisdigit.c \
		./srcs/utils/ft_strjoin.c \
		./srcs/utils/ft_strlcpy.c \
		./srcs/utils/ft_strlen.c \
		./srcs/utils/ft_strnchr.c \
		./srcs/utils/ft_strnchrn.c \
		./srcs/utils/ft_strncmp.c \
		./srcs/utils/ft_strndup.c \
		./srcs/utils/ft_strnstr.c \
		./srcs/utils/ft_strreplace.c \
		./srcs/utils/ft_strtolower.c \
		./srcs/utils/ft_strtrim.c \
		./srcs/utils/ft_substr.c \
		./srcs/utils/ft_tolower.c \
		./srcs/utils/hashtable.c \
		./srcs/utils/hashtable1.c \
		./srcs/utils/hashtable2.c \
		./srcs/utils/is_seperator.c \
		./srcs/utils/is_specialcar.c \
		./srcs/utils/linkedlist.c \
		./srcs/utils/linkedlist1.c \
		./srcs/utils/ternary.c

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