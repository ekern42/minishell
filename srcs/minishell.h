/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:57 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 14:40:13 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

/* INCLUDES */
# include <unistd.h>
# include <stdio.h>
# include <signal.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/big_lib.h"

/* STRUCT */
typedef struct	s_envp_list
{
	char				*name;
	void				*data;
	struct	s_envp_list	*next;
}	t_envp_list;

typedef struct	s_info
{
	char				*command_line;
	char				**seg_command_line;
	struct s_envp_list	*envp;
	struct s_envp_list	*var;
}	t_info;


/* commands */
int	fc_commands(t_info *info);

/* errors */
void	fc_error(t_info *info, int a);
size_t	fc_strlen(const char *str);

/* free */
void	fc_final_free(t_info *info);
void	fc_free_seg_command_line(t_info *info);

/* init */
static void fc_start_up(void);
static void	fc_envp_init(t_info *info, char **envp);
int			fc_init(t_info *info, char **envp);

/* quotes */
static void fc_dbl_quotes(t_info *info);
static void fc_sgl_quotes(t_info *info);
int			fc_quotes(t_info *info);

/* signal */
void		fc_control_d(t_info *info);
static void fc_control_backslash(int num);
static void fc_control_c(int num);
int			fc_signal(t_info *info);

/* split */
void	fc_split_line(t_info *info);

/* utils */
void	fc_split_line(t_info *info);
void	fc_exit(t_info *info);
void	fc_test(char **envp);

/* variable */
void	fc_variable_command(t_info *info);
int		fc_check_variable(t_info *info);

/* main.c */
int	fc_prompt(t_info *info);

#endif