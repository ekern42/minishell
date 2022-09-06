# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/09 13:40:58 by ekern             #+#    #+#              #
#    Updated: 2022/09/06 12:10:53 by angelo           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

MINISHELL = minishell
NAME = $(MINISHELL)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

INCLUDES = srcs/minishell.h

LIBFT = libft.a
LIBFT_DIR = libft
LIBFT_FILE = $(LIBFT_DIR)/$(LIBFT)

SRC_COMMANDS =	\
	srcs/commands/commands.c	\
	srcs/commands/fc_echo.c

SRC_ERRORS =	\
	srcs/errors/errors.c

SRC_FREE =	\
	srcs/free/free_time.c

SRC_INIT =	\
	srcs/init/init.c	\

SRC_QUOTES =	\
	srcs/quotes/quotes.c	\

SRC_SIGNAL =	\
	srcs/signal/signal.c

SRC_SPLIT =	\
	srcs/split/split_line.c

SRC_UTILS =	\
	srcs/utils/utils.c

SRC_VARIABLE =	\
	srcs/variable/variable.c

SRC_ROOT = srcs/main.c


SRCS =	\
	$(SRC_COMMANDS)	\
	$(SRC_ERRORS)	\
	$(SRC_FREE)	\
	$(SRC_INIT)	\
	$(SRC_QUOTES)	\
	$(SRC_SIGNAL)	\
	$(SRC_SPLIT)	\
	$(SRC_UTILS)	\
	$(SRC_VARIABLE)	\
	$(SRC_ROOT)


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