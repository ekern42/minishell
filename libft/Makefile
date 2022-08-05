# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/21 11:30:17 by ekern             #+#    #+#              #
#    Updated: 2022/04/12 16:31:43 by ekern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIBFT = libft
NAME = $(LIBFT)

ARCHIVE = $(NAME).a
AR = ar
ARFLAGS = crs

CC = gcc
CFLAGS = -Werror -Wextra -Wall

INCLUDES = \
	libft_srcs/libft.h	\
	printf/printf.h		\
	gnl/get_next_line.h

SRCS = \
	libft_srcs/ft_isalpha.c	\
	libft_srcs/ft_isdigit.c	\
	libft_srcs/ft_isalnum.c	\
	libft_srcs/ft_isascii.c	\
	libft_srcs/ft_isprint.c	\
	libft_srcs/ft_strlen.c	\
	libft_srcs/ft_memset.c	\
	libft_srcs/ft_bzero.c	\
	libft_srcs/ft_memcpy.c	\
	libft_srcs/ft_memmove.c	\
	libft_srcs/ft_strlcpy.c	\
	libft_srcs/ft_strlcat.c	\
	libft_srcs/ft_toupper.c	\
	libft_srcs/ft_tolower.c	\
	libft_srcs/ft_strchr.c	\
	libft_srcs/ft_strrchr.c	\
	libft_srcs/ft_strncmp.c	\
	libft_srcs/ft_memchr.c	\
	libft_srcs/ft_memcmp.c	\
	libft_srcs/ft_strnstr.c	\
	libft_srcs/ft_atoi.c	\
	libft_srcs/ft_calloc.c	\
	libft_srcs/ft_strdup.c	\
	libft_srcs/ft_substr.c	\
	libft_srcs/ft_strjoin.c	\
	libft_srcs/ft_strtrim.c	\
	libft_srcs/ft_split.c	\
	libft_srcs/ft_itoa.c	\
	libft_srcs/ft_strmapi.c	\
	libft_srcs/ft_striteri.c		\
	libft_srcs/ft_putchar_fd.c		\
	libft_srcs/ft_putstr_fd.c		\
	libft_srcs/ft_putendl_fd.c		\
	libft_srcs/ft_putnbr_fd.c		\
	libft_srcs/fc_dec_to_binary.c	\
	libft_srcs/ft_atol.c			\
	printf/ft_printf.c				\
	printf/fc_printf_utils.c		\
	printf/fc_check.c				\
	printf/fc_nbrprint.c			\
	printf/fc_specprint.c			\
	printf/fc_charaprint.c			\
	gnl/get_next_line.c				\
	gnl/get_next_line_utils.c

OBJS = ${SRCS:c=o}

all : $(NAME)

$(LIBFT) : $(OBJS)
	@$(AR) $(ARFLAGS) $(ARCHIVE) $^

%.o : %.c $(INCLUDES)
	@$(CC) $(CFLAGS) -c $<

clean :
	@rm -f $(OBJS)

fclean : clean
	@rm -f $(ARCHIVE) $(NAME)

re : fclean all

.PHONY : all clean fclean re