/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:57 by ekern             #+#    #+#             */
/*   Updated: 2022/09/22 16:27:39 by ekern            ###   ########.fr       */
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
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/big_lib.h"

/* STRUCT */

/*
	bool	re_append;	// >>
	bool	re_del;		// <<
	bool	re_input;	// <
	bool	re_output;	// >
*/

typedef struct s_quotes
{
	char			type;
	int				begin;
	int				end;
	struct s_quotes	*next;
}				t_quotes;

typedef struct s_lex_info
{
	bool	pipes;
	int		nbr_pipe;
	bool	sgl_quotes;
	int		nbr_pair_sgl_q;
	bool	dbl_quotes;
	int		nbr_pair_dbl_q;
	bool	variable;
	int		nbr_variable;
	bool	re_append;
	int		nbr_re_append;
	bool	re_del;
	int		nbr_re_del;
	bool	re_input;
	int		nbr_re_input;
	bool	re_output;
	int		nbr_re_output;
	bool	error;
}	t_lex_info;

typedef struct s_execution
{
	char	***cmds;
	pid_t	pid_init;
	pid_t	pid_other;
	int		pipe_init;
	int		size_seg_cmd_line;
	int		idx_for_pipe;
	int		fd[2];
	int		**fd_final;
	int		i;
	int		j;
}	t_execution;

typedef struct s_info
{
	char			*command_line;
	char			**seg_command_line;
	int				b_sub_str;
	char			**cpy_cmd;
	int				idx_seg_cmd_line;
	char			*path;
	t_execution		*exe;
	int				pair_sgl_quotes;
	int				pair_dbl_quotes;
	struct s_list	*envp;
	struct s_list	*small_str_list;
	t_lex_info		*lex;
	t_quotes		*quotes_list;
}	t_info;

/* execution */
int		fc_execution(t_info *info);
int		fc_builtins_or_execve(t_info *info);

/* execution/builtins */
int		fc_builtins(t_info *info);
int		fc_cd(t_info *info);
int		fc_echo(t_info *info);
int		fc_env(t_info *info);
int		fc_exit(t_info *info);
int		fc_export(t_info *info);
int		fc_pwd(t_info *info);
int		fc_unset(t_info *info);

/* execution/execve */
int		fc_execve(t_info *info);
void	*fc_path_for_execve(t_info *info);

/* execution/redirections */
//int		fc_pipe(t_info *info);
int		fc_stdin_to_stdout(t_info *info); //Donc à gauche du pipe
int		fc_stdout_to_stdin(t_info *info); //Donc à droite du pipe

/* errors */
void	fc_error(t_info *info, int a);
int		fc_error_exe(char *error, int code_return);
int		fc_error_exe2(int code_return);

/* free */
void	fc_final_free(t_info *info);
void	fc_free_seg_command_line(t_info *info);

/* init */
int		fc_init(t_info *info, t_lex_info *lex, char **envp);
void	fc_init_seg_cmd_line(t_info *info);

/* Lexer */
void	fc_init_lexer(t_info *info);
void	fc_lexer(t_info *info);
int		fc_check_lex(t_info *info, int a);
int		fc_lex_pipes(t_info *info, int a);
int		fc_lex_quotes(t_info *info, int a);
int		fc_lex_redirections(t_info *info, int a);
void	fc_lex_variables(t_info *info);

/* parsing */
int		fc_parsing(t_info *info);
int		fc_go_until_pipe(t_info *info);
int		fc_go_until_next(t_info *info);
char	**fc_cpy_cmd(t_info *info);
char	**fc_cpy_cmd2(t_info *info);
//int		fc_separate_cmd_pipe(t_info *info);
//char	**fc_copy_pipe_cmd(char **cmd_line);
int		fc_small_str_with_quote(t_info *info, t_quotes *temp, int a);
void	fc_small_str_without_quote(t_info *info, t_quotes *temp, int a);
void	fc_seg_str(t_info *info);

/* signal */
void	fc_control_d(t_info *info);
int		fc_signal(t_info *info);

/* utils */
size_t	fc_strlen(const char *str);
void	fc_test(char **envp);
void	*fc_find_envp_with_name(t_info *info, char *var_env);
void	*fc_find_envp_without_name(t_info *info, char *var_env);
void	fc_print_seg_cmd_line(t_info *info);

/* variable */
void	fc_variable_command(t_info *info);
int		fc_check_variable(t_info *info);

/* main.c */
int		fc_prompt(t_info *info);

#endif
