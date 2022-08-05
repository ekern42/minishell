# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/26 12:00:04 by ekern             #+#    #+#              #
#    Updated: 2022/03/02 17:33:29 by ekern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = ft_printf.a

AR = ar
ARFLAGS = crs

CC = gcc
CFLAGS = -Wall -Werror -Wextra

INCLUDES = printf.h

SRCS =	\
	ft_printf.c			\
	fc_printf_utils.c	\
	fc_check.c			\
	fc_charaprint.c		\
	fc_nbrprint.c		\
	fc_specprint.c

OBJS := ${SRCS:c=o}

all : $(NAME)

$(NAME) : $(OBJS)
	@$(AR) $(ARFLAGS) $@ $^

%.o : %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $<

bonus : ${NAME}

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re