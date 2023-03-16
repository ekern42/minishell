# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 16:27:19 by gudias            #+#    #+#              #
#    Updated: 2023/03/16 16:22:59 by ekern            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= minishell

CC		= gcc
CFLAGS	= -Werror -Wextra -Wall

INCL	= -I incs -I $(HOME)/.brew/opt/readline/include
RM		= rm -f

LIBFT	= libft/libft.a

SRCSDIR	= srcs
OBJSDIR	= objs

SRCS	=	minishell.c \
			initialisation.c \
			clean_program.c \
			parsing.c \
			run_cmd.c \
			errors.c \
			signal_utils_main.c \
			builtin_utils.c \
			builtin/unset_builtin.c \
			builtin/cd_builtin.c \
			builtin/env_builtin.c \
			builtin/exit_builtin.c \
			builtin/echo_builtin.c \
			builtin/pwd_builtin.c \
			builtin/export_builtin.c \
			array_utils.c \
			temporaire.c \
			here_doc.c \
			prompt.c \
			redirection.c \
			execution.c \
			assignations.c \
			utils/termios_utils.c \
			utils/linklist_utils_01.c \
			utils/linklist_utils_02.c \
			utils/quote_info_utils_01.c \
			utils/quote_info_utils_02.c \
			utils/space_maker_pipeline.c \
			utils/space_maker_chevron.c \
			utils/space_maker_utils.c \
			utils/split_shell_line.c \
			utils/translate_dollar_utils_01.c \
			utils/translate_dollar_utils_02.c \
			utils/chevron_segment_utils.c \
			utils/signal_utils_fork_child.c \
			utils/signal_utils_fork_parent.c \
			utils/check_grammar.c \
			utils/check_grammar_chevron.c \
			utils/check_grammar_pipeline.c	\
			fc_parsing.c \
			final_seg.c \
			parsing_utils.c \
			seg_str.c \
			sub_str.c \
			utils.c \
			lexer.c	\
			lex_pipes.c	\
			lex_quotes.c	\
			lex_redirections.c	\
			lex_variables.c \
			init.c \
			free_time.c

OBJS	= $(SRCS:%.c=$(OBJSDIR)/%.o)
DBG_OBJS = $(SRCS:%.c=$(OBJSDIR)/%_dbg.o)

$(OBJSDIR)/%.o: $(SRCSDIR)/%.c
	@echo "$(YELLOW)Compiling $(DEFAULT)$<"
	@mkdir -p $(OBJSDIR) $(OBJSDIR)/builtin $(OBJSDIR)/utils
	@$(CC) $(CFLAGS) $(INCL) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@echo "$(YELLOW)Creating executable..$(DEFAULT)"
	@$(CC) $(CFLAGS) $^  -L$(HOME)/.brew/opt/readline/lib -lreadline -o $@
	@echo "$(GREEN)---> ./$@ is ready$(DEFAULT)"

$(LIBFT):
	@echo "$(YELLOW)Preparing Libft..$(DEFAULT)"
	@make -C libft 1>/dev/null 2>/dev/null
	@echo "$(CYAN)---> Libft ready$(DEFAULT)"

clean:
	@$(RM) -r $(OBJSDIR)
	@echo "$(RED)Removed $(CYAN)objs/$(DEFAULT)"

fclean: clean
	@$(RM) $(NAME)
	@echo "$(RED)Removed $(CYAN)./$(NAME)$(DEFAULT)"

libclean: 
	@make fclean -C libft 1>/dev/null 2>/dev/null
	@echo "$(RED)Removed $(CYAN)Libft$(DEFAULT)"

debug: $(DBG_OBJS) $(LIBFT)
	@echo "$(YELLOW)Preparing files for debug...$(DEFAULT)"
	@$(CC) $(CFLAGS) $^ -L$(HOME)/.brew/opt/readline/lib -lreadline -o debug_$(NAME)
	@echo "$(GREEN)----> ./debug_$(NAME) is ready$(DEFAULT)"
	@echo "$(CYAN)Launching LLDB...$(DEFAULT)"
	@lldb ./debug_$(NAME)
	@echo "$(RED)Removed $(CYAN)./debug_$(NAME)$(DEFAULT)"
	@$(RM) debug_$(NAME)

$(OBJSDIR)/%_dbg.o: $(SRCSDIR)/%.c
	@mkdir -p $(OBJSDIR) $(OBJSDIR)/builtin $(OBJSDIR)/utils
	@$(CC) -g3 $(INCL) -c $< -o $@

fullclean: fclean libclean

bonus: re

re: fclean all

.PHONY: all clean fclean re bonus libclean fullclean

#COLORS
RED = \033[1;31m
GREEN = \033[1;32m
YELLOW = \033[1;33m
CYAN = \033[1;36m
DEFAULT = \033[0m
