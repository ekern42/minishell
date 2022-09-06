/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/09/06 16:09:29 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <stdbool.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/big_lib.h"

/* STRUCT */

typedef struct		s_lex_info
{
	bool	pipes;
	bool	sgl_quotes;
	bool	dlb_quotes;
	bool	variable;
	bool	re_append;	// >>
	bool	re_del;		// <<
	bool	re_input;	// <
	bool	re_output;	// >

	
}					t_lex_info;

typedef struct		s_info
{
	char			*command_line;
	char			**seg_command_line;
	int				pair_sgl_quotes;
	int				pair_dbl_quotes;
	struct s_list	*envp;
	struct s_list	*var;
}					t_info;

/* commands */
int		fc_builtins(t_info *info);
int		fc_echo(t_info *info);

/* errors */
void	fc_error(t_info *info, int a);
size_t	fc_strlen(const char *str);

/* free */
void	fc_final_free(t_info *info);
void	fc_free_seg_command_line(t_info *info);

/* init */
//static void	fc_start_up(void);
//static void	fc_envp_init(t_info *info, char **envp);
//static void	fc_init_lexer(t_lex_info *lex);
int		fc_init(t_info *info, t_lex_info *lex, char **envp);

/* quotes */
//static void fc_dbl_quotes(t_info *info);
//static void fc_sgl_quotes(t_info *info);
int		fc_quotes(t_info *info);

/* signal */
void	fc_control_d(t_info *info);
//static void	fc_control_backslash(int num);
//static void	fc_control_c(int num);
int		fc_signal(t_info *info);

/* split */
void	fc_split_line(t_info *info);

/* utils */
size_t	fc_strlen(const char *str);
int		fc_argc_wt_exe(t_info *info);
void	fc_exit(t_info *info);
void	fc_test(char **envp);

/* variable */
void	fc_variable_command(t_info *info);
int		fc_check_variable(t_info *info);

/* main.c */
int		fc_prompt(t_info *info);

#endif