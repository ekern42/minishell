/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:57 by ekern             #+#    #+#             */
/*   Updated: 2022/10/07 12:42:39 by angelo           ###   ########.fr       */
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
# include <fcntl.h>
# include <dirent.h>
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
}	t_quotes;

typedef struct s_lex_info // lexical qqch -> vérifie chaque caractère
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
	char	**cmds_execve;
//	char	**str_left;
	char	*path;
	int		index;
	pid_t	*pid_lst;
	pid_t	w_pid;
	pid_t	pid_init;
	pid_t	pid_other;
	int		pipe_init;
	char	*buffer;
	char	*buff;
	int		file;
	int		size_buffer;
	int		fd[2];
}	t_execution;

typedef struct s_builtin
{
	struct dirent	*entity;
	DIR				*dir;
}	t_builtin;

typedef struct s_info
{
	char			*command_line;
	int				b_sub_str;
	int				nbr_sstr;
	int				idx;
	int				idx_re;
	char			**str_left;
	t_builtin		*b;
	t_execution		*exe;
	int				pair_sgl_quotes;
	int				pair_dbl_quotes;
	struct stat		*buffer3;
	struct s_list	*envp;
	struct s_list	*small_str_list;
	t_lex_info		*lex;
	t_quotes		*quotes_list;
}	t_info;

/* execution */
int		fc_execution(t_info *info);
int		fc_exe_without_re(t_info *info);
int		fc_exe_with_re(t_info *info);
char **	fc_create_tmp_str(t_info *info); // emplacement temporaire
void	fc_print_tmp_str(char **str); // emplacement temporaire
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
int		fc_execve_redir(t_info *info);
int		fc_putstr_fd_re(char *str, char *arg);
int		fc_execute(char **arg, char *path, int tmp_fd, char **env);
int		fc_execve_mlt_pipes(t_info *info);
void	*fc_path_for_execve(t_info *info);
void	*fc_path_mlt_pipes(t_info *info, int index_re);

/* execution/redirections */
int		fc_stdin_to_stdout(t_info *info); //Donc à gauche du pipe
int		fc_stdout_to_stdin(t_info *info); //Donc à droite du pipe
int		fc_stdout_and_stdin(t_info *info);

int		fc_re_append(t_info *info); // >>
int		fc_find_size_buffer(t_info *info);
int		fc_re_output(t_info *info); // >

/* errors */
void	fc_error(t_info *info, int a);
int		fc_error_exe(char *error, int code_return);
int		fc_error_exe2(int code_return);
int		fc_error_tmp(int code_return, char *error_message);

/* free */
void	fc_final_free(t_info *info);
void	fc_free_t_list(t_info *info);
void	fc_free_t_list_spec(t_info *info);
void	fc_quote_list_free(t_info *info);

/* init */
int		fc_init(t_info *info, t_lex_info *lex, char **envp);

/* lexer */
void	fc_init_lexer(t_info *info);
void	fc_lexer(t_info *info);
int		fc_check_lex(t_info *info, int a);
int		fc_lex_pipes(t_info *info, int a);
int		fc_lex_quotes(t_info *info, int a);
int		fc_lex_redirections(t_info *info, int a);
void	fc_lex_variables(t_info *info);

/* parsing */
int		fc_parsing(t_info *info);
void	fc_print_for_pipe(t_info *info);
int		fc_small_str_with_quote(t_info *info, t_quotes *temp, int a);
void	fc_small_str_without_quote(t_info *info, t_quotes *temp, int a);
void	fc_seg_str(t_info *info);
void	fc_final_seg(t_info *info);

/* signal */
void	fc_control_d(t_info *info);
int		fc_signal(t_info *info);

/* utils */
size_t	fc_strlen(const char *str);
void	fc_test(char **envp);
void	*fc_find_envp_without_name(t_info *info, char *var_env);
void	fc_print_cmds(t_info *info);
int		fc_check_is_redir(t_info *info);
int		fc_size_str(t_info *info);
void	*fc_create_left_str(t_info *info);
void	fc_print_str_left(t_info *info);
int		fc_find_idx_file(t_info *info, char *re, int size);

/* variable */
void	fc_variable_command(t_info *info);
int		fc_check_variable(t_info *info);

/* main.c */
int		fc_prompt(t_info *info);
void	fc_print_list(t_info *info);


#endif
