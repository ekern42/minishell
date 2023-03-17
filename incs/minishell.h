/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:17:55 by gudias            #+#    #+#             */
/*   Updated: 2023/03/17 12:00:36 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
/* ************************************************************************** */
# include "../libft/includes/libft.h"
# include "errors.h"
# include "colors.h"
/* ************************************************************************** */
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdbool.h>
# include <errno.h>
# include <string.h>
# include <fcntl.h>
/* ************************************************************************** */
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/wait.h>
# include <signal.h>
# include <termios.h>
/* ************************************************************************** */

typedef struct s_quotes
{
	char			type;
	int				begin;
	int				end;
	struct s_quotes	*next;
}	t_quotes;

typedef struct s_var
{
	char			*content;
	char			*name;
	struct s_var	*next;
}	t_var;

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

typedef struct s_builtin
{
	int				local_fd;
	int				fd_ex;
	int				option;
	int				j;
	struct dirent	*entity;
}	t_builtin;

typedef struct s_execution
{
	char	***cmds;
	char	**cmds_exe;
	char	**envp_exe;
	char	*path;
	int		is_re;
	pid_t	pid;
	int		fd[2];
	int		tmp_fd;
	int		fd_re;
}	t_execution;
/*
typedef struct s_info
{
	char			*command_line;
	int				*begin;
	int				*end;
	int				b_sub_str;
	int				nbr_sstr;
	t_builtin		*b;
	t_execution		*exe;
	struct s_list	*envp;
	char			**envp_lol;
	struct s_list	*small_str_list;
	t_lex_info		*lex;
	t_quotes		*quotes_list;
	t_var			*var_list;
}	t_vars;
*/
typedef struct s_quote_info
{
	int		cnt_char_realquote;
	char	last_char_realquote;
	bool	flag_inside_realquote;
	bool	flag_entering_realquote;
	bool	flag_exiting_realquote;	
}	t_quote_info;

/* ************************************************************************** */

typedef struct s_sig
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;
	struct sigaction	sa_sigchild;
}	t_sig;
// ----------------------------------------
typedef struct s_env
{
	char			*name;
	char			*data;
	struct s_env	*next;
}	t_env;
// ----------------------------------------
typedef struct s_vars
{
	char			*new_line;
	int				stdin_fd;
	int				stdout_fd;
	int				stderr_fd;
	t_env			*env;
	t_env			*loc;
	t_sig			sig;
	int				segments_count;
	char			*command_line;
	int				*begin;
	int				*end;
	int				b_sub_str;
	int				nbr_sstr;
	t_builtin		*b;
	t_execution		*exe;
	struct s_list	*envp;
	char			**envp_lol;
	struct s_list	*small_str_list;
	t_lex_info		*lex;
	t_quotes		*quotes_list;
	t_var			*var_list;
}	t_vars;

/* ************************************************************************** */

typedef struct s_cmd
{
	int		fd_in;
	int		fd_out;
	char	**args;
}	t_cmd;

/* ************************************************************************** */
void	init_signal_main(t_sig *s);
void	handler_signal_main(int sig_code);
// --------------------------------------------
void	init_signal_fork_child(t_sig *s);
void	init_signal_fork_child_hd(t_sig *s);
// --------------------------------------------
void	init_signal_fork_parent(t_sig *s);
void	handler_signal_fork_parent(int sig_code);
/* ************************************************************************** */
void	initialisation(t_vars *vars, char **envp);
void	init_env(t_vars *vars, char **envp);
void	clean_program(t_vars *vars);
/* ************************************************************************** */
//char	**lexing(t_vars *vars, char *line);
void	handle_segments(t_vars *vars, char ***segments);
void	parse_line(t_vars *vars, char **line, int output);

int		execute_cmd(t_vars *vars, t_cmd *cmd, int i);
void	get_redirections(t_vars *vars, t_cmd *cmd);
void	set_redirections(t_cmd *cmd);
void	reset_redirections(t_vars *vars, t_cmd *cmd);
void	here_doc(char *limiter);

int		is_builtin(char *cmd);
int		exec_builtin(t_vars *vars, char **cmd_args);
int		run_cmd(t_vars *vars, t_cmd *cmd, int i);
void	exec_cmd(t_vars *vars, char **cmd_args);

int		check_assignations(t_vars *vars, t_cmd *cmd);
int		name_is_valid(char *name);

int		exit_builtin(t_vars *vars, char **cmd_args);
int		echo_builtin(char **cmd_args);
int		pwd_builtin(t_vars *vars, char **cmd_args);
int		export_builtin(t_vars *vars, char **cmd_args);
int		unset_builtin(t_vars *vars, char **cmd_args);
int		cd_builtin(t_vars *vars, char **cmd_args);
int		env_builtin(t_vars *vars);
int		loc_builtin(t_vars *vars);

char	*show_prompt(t_vars *vars);
void	launch_message(void);
// ------------------------------------------------------ temporaire.c
bool	does_word_match(char *str, char *hard_text);
bool	does_wordstart_match(char *str, char *hard_text);
void	ft_free_null(char **ptr);
int		openfilex(char *filepath, int o_flag);
// -------------------------------------------------- linklist_utils.c
void	print_var(t_env *var_head);
t_env	*get_var(t_env *var_head, char *var_name);
bool	does_var_exist(t_env *var_head, char *var_name);
void	update_var(t_env **var_head, char *var_name, char *new_data);
void	add_var(t_env **var_head, char *name, char *data);
void	remove_var(t_env **var_head, char *var_name);
int		size_var_list(t_env *var_head);
void	free_var_list(t_env **var_head);
// ----------------------------------------------------- array_utils.c
char	**conv_list_to_array(t_env *var_head);
void	print_array(char **array);
void	free_array(char **array);
// -------------------------------------------------------------------
char	**split_shell_line(char *line, char separator);
char	*chevron_space_maker(char *line);
char	*pipeline_space_maker(char *line);
char	*insert_space_before_actual_pos(char *line, int *actual_position);
char	*insert_space_after_actual_pos(char *line, int *actual_position);
// ------------------------------------------------ translate_dollar.c
char	**translate_dollars_all(char **array, t_vars *vars);
char	*translate_dollar(char *str, t_vars *vars);
bool	is_char_for_dolvar_name(char c);
bool	is_vardol(char *str, int i);
int		get_end_pos_vardol(char *str, int start_pos);
char	*substitute_vardol(char *str, int *start_pos, t_vars *vars);
char	*delete_char(char *str, int *i);
// ------------------------------------------------ quote_info_utils.c
void	init_quote_info(t_quote_info *qti);
void	refresh_quote_info(t_quote_info *qti, char actual_char);
bool	is_good_number_of_realquote(t_quote_info *qti);
bool	is_inside_realquote(t_quote_info *qti);
bool	is_outside_realquote(t_quote_info *qti);
bool	is_entering_realquote(t_quote_info *qti);
bool	is_exiting_realquote(t_quote_info *qti);
bool	is_inside_single_realquote(t_quote_info *qti);
// -------------------------------------------------------------------
bool	is_line_with_correct_quote(char *line, t_vars *vars);
// -------------------------------------------------------------------
bool	is_grammar_correct(char *line, t_vars *vars);
bool	is_grammar_chevron_correct(char *line, t_vars *vars);
bool	is_grammar_pipeline_correct(char *line, t_vars *vars);
// ------------------------------------------- chevron_segment_utils.c
int		get_segment_fd_in(t_vars *vars, char **array);
int		get_segment_fd_out(char **array);
void	clear_chevron_segment(char **array);
// -------------------------------------------------------------------
void	err_msg(char *msg);
void	exit_msg(char *msg);
int		manage_perror(char *remark, int error_code);
// -------------------------------------------------------------------
void	stop_echoctl(void);
void	start_echoctl(void);
void	stop_echoctl_fd(int fd);
void	start_echoctl_fd(int fd);
// -------------------------------------------------------------------

int		fc_init(t_vars *info, char **envp);

/* lexer */
void	fc_init_lexer(t_vars *info);
void	fc_lexer(t_vars *info);
int		fc_check_lex(t_vars *info, int a);
void	fc_print_list(t_vars *info);
int		fc_lex_pipes(t_vars *info, int a);
int		fc_lex_quotes(t_vars *info, int a);
int		fc_lex_redirections(t_vars *info, int a);
void	fc_lex_variables(t_vars *info);

/* parsing */
int		fc_parsing(t_vars *info);
void	fc_print_for_pipe(t_vars *info);
int		fc_small_str_with_quote(t_vars *info, t_quotes *temp, int a);
void	fc_small_str_without_quote(t_vars *info, t_quotes *temp, int a);
void	fc_seg_str(t_vars *info);
int		fc_small_str_common2_sec(t_vars *info, int a);
void	fc_sub_str(t_vars *info, int a);
void	fc_final_seg(t_vars *info);

/* utils */
size_t	fc_strlen(const char *str, char c);
void	fc_test(char **envp);
int		fc_dblstrlen(char **tab);
void	fc_print_cmds(t_vars *info);
int		fc_valide_name(char *str);
char	*fc_find_var(t_list *envp, char *name);

/* variable */
int		fc_check_variable(t_vars *info, int a, int b);
void	fc_check_dollar(t_vars *info);
void	fc_dollar_details(t_vars *info, char *str, int n);
t_list	*fc_sub_dollar(t_list *sub_temp, t_vars *info, char *str, int l);
void	fc_replace_dollar(t_vars *info, t_list *sub_temp);
void	fc_dollar_fusion(t_vars *info, t_list *sub);
void	fc_malloc_dollar(t_vars *info, int n);
int		fc_strcmp_spec(char *s1, char *s2);
int		fc_order_re(t_vars *info);
void	fc_free_t_list_spec(t_vars *info);
void	fc_final_free(t_vars *info);
void	fc_error_lex(t_vars *info, char c);

#endif
