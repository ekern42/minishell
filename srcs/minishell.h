/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:57 by ekern             #+#    #+#             */
/*   Updated: 2022/10/17 14:25:34 by ekern            ###   ########.fr       */
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

typedef struct s_execution
{
	char	***cmds;
	char	**cmds_execve;
	char	*path;
	int		fd[2];
	int		tmp_fd;
}	t_execution;

typedef struct s_builtin
{
	int				local_fd;
	int				option;
	int				j;
	struct dirent	*entity;
	DIR				*dir;
}	t_builtin;

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
}	t_info;

/* execution */
int		fc_execution(t_info *info);
int		fc_is_last_command(t_info *info, int i);
int		fc_not_in_last_command(t_info *info, int i);
int		fc_builtins_or_execve(t_info *info, int i, char *std);
int		fc_builtins(t_info *info, int i);
int		fc_is_builtin(t_info *info, int i);

/* execution/builtins */
int		fc_cd(t_info *info);
int		fc_echo(t_info *info, int i);
int		fc_env(t_info *info, int i);
int		fc_exit(t_info *info);
int		fc_export(t_info *info);
int		fc_pwd(t_info *info, int i);
int		fc_unset(t_info *info);

/* execution/execve */
int		fc_execve(t_info *info, int i, char *std);
void	*fc_path_for_execve(t_info *info, int index_re);
void	*fc_find_envp_without_name(t_info *info, char *var_env);

/* execution/redirections */
int		fc_stdin_to_stdout(t_info *info); //Donc à gauche du pipe
int		fc_stdout_to_stdin(t_info *info); //Donc à droite du pipe
int		fc_re_append(t_info *info, int a, int i); // >>
int		fc_re_output(t_info *info, int a, int i); // >
int		fc_re_input(t_info *info, int a, int i); // <
int		fc_re_del(t_info *info, int a, int i); // <<

/* errors */
void	fc_error(t_info *info, int a);
int		fc_error_exe(int code_return, char *error_message);
int		fc_putstr_fd_error(char *str, t_info *info);

/* free */
void	fc_final_free(t_info *info);
void	fc_free_t_list(t_info *info);
void	fc_free_t_list_spec(t_info *info);

/* init */
int		fc_init(t_info *info, char **envp);

/* lexer */
void	fc_init_lexer(t_info *info);
void	fc_lexer(t_info *info);
int		fc_check_lex(t_info *info, int a);
void	fc_print_list(t_info *info);
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
int		fc_small_str_common2_sec(t_info *info, int a);
void	fc_sub_str(t_info *info, int a);
void	fc_final_seg(t_info *info);

/* signal */
void	fc_control_d(t_info *info);
int		fc_signal(t_info *info);

/* utils */
size_t	fc_strlen(const char *str);
void	fc_test(char **envp);
int		fc_dblstrlen(char **tab);
void	fc_print_cmds(t_info *info);
void	fc_print_var_list(t_info *info);

/* variable */
int		fc_check_variable(t_info *info, int	a, int b);
void	fc_check_dollar(t_info *info);
void	fc_dollar_details(t_info *info, char *str, int n);
t_list	*fc_sub_dollar(t_list *sub_temp, t_info *info, char *str, int l);
void	fc_replace_dollar(t_info *info, t_list *sub_temp);
void	fc_dollar_fusion(t_info *info, t_list *sub);
void	fc_malloc_dollar(t_info *info, int n);
int		fc_strcmp_spec(char *s1, char *s2);

/* main.c */
int		fc_prompt(t_info *info);

#endif
