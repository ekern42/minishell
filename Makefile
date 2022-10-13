# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:40:58 by ekern             #+#    #+#              #
#    Updated: 2022/10/13 17:22:52 by aprosper         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


MINISHELL = minishell
NAME = $(MINISHELL)

CC = gcc
CFLAGS = -Werror -Wextra -Wall -g3 
#-fsanitize=address

INCLUDES = srcs/minishell.h

LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)

SRC_BUILTINS =	\
	srcs/execution/builtins/fc_cd.c	\
	srcs/execution/builtins/fc_echo.c	\
	srcs/execution/builtins/fc_env.c	\
	srcs/execution/builtins/fc_exit.c	\
	srcs/execution/builtins/fc_export.c	\
	srcs/execution/builtins/fc_pwd.c	\
	srcs/execution/builtins/fc_unset.c

SRC_EXECVE =	\
	srcs/execution/execve/fc_execve.c	\
	srcs/execution/execve/fc_path_for_execve.c

SRC_REDIRECTIONS =	\
	srcs/execution/redirections/fc_re_append.c	\
	srcs/execution/redirections/fc_re_output.c	\
	srcs/execution/redirections/fc_re_input.c	\
	srcs/execution/redirections/fc_re_del.c	\
	srcs/execution/redirections/pipe.c

SRC_EXECUTION =	\
	srcs/execution/fc_execution.c	\
	srcs/execution/fc_builtins_or_execve.c	\
	srcs/execution/fc_is_last_command.c	\
	srcs/execution/fc_not_in_last_command.c

SRC_ERRORS =	\
	srcs/errors/errors.c

SRC_FREE =	\
	srcs/free/free_time.c

SRC_INIT =	\
	srcs/init/init.c

SRC_LEXER = \
	srcs/lexer/lexer.c	\
	srcs/lexer/lex_pipes.c	\
	srcs/lexer/lex_quotes.c	\
	srcs/lexer/lex_redirections.c	\
	srcs/lexer/lex_variables.c

SRC_PARSING =	\
	srcs/parsing/fc_parsing.c	\
	srcs/parsing/sub_str.c	\
	srcs/parsing/seg_str.c	\
	srcs/parsing/final_seg.c

SRC_SIGNAL =	\
	srcs/signal/signal.c

SRC_UTILS =	\
	srcs/utils/utils.c

SRC_VARIABLE =	\
	srcs/variable/variable.c

SRC_ROOT = srcs/main.c

SRCS =	\
	$(SRC_BUILTINS)	\
	$(SRC_EXECVE)	\
	$(SRC_REDIRECTIONS)	\
	$(SRC_EXECUTION)	\
	$(SRC_ERRORS)	\
	$(SRC_FREE)	\
	$(SRC_INIT)	\
	$(SRC_PARSING)	\
	$(SRC_SIGNAL)	\
	$(SRC_UTILS)	\
	$(SRC_VARIABLE)	\
	$(SRC_ROOT)		\
	$(SRC_LEXER)

OBJS = ${SRCS:c=o}

all : $(LIBFT) $(NAME)

$(MINISHELL) : $(OBJS)
	$(CC) $(CFLAGS) $^ $(LIBFT_FILE) -lreadline -o $(NAME)

srcs/%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

big_clean : fclean $(LIBFT_FILE)_fclean

re : fclean all

# Libft

$(LIBFT) : $(LIBFT_FILE)

$(LIBFT_FILE) :
	@make --no-print-directory -C $(LIBFT_DIR)

$(LIBFT_FILE)_fclean :
	@make --no-print-directory -C $(LIBFT_DIR) fclean

.PHONY : all clean fclean big_clean re 