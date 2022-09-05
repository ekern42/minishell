/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:57 by ekern             #+#    #+#             */
/*   Updated: 2022/09/01 14:25:47 by ekern            ###   ########.fr       */
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
	char					*name;
	void					*data;
	struct	s_envp_list	*next;
}				t_envp_list;

typedef struct	s_info
{
	char	*command_line;
	char	**seg_command_line;
	struct s_envp_list *envp;
	struct s_envp_list *var;
}				t_info;
/* SRCS */

void fc_error(t_info *info, int a);
size_t	fc_strlen(const char *str);
int	fc_signal(t_info *info);
void fc_control_d(t_info *info);
int	fc_init(t_info *info, char **envp);
void fc_split_line(t_info *info);
void fc_final_free(t_info *info);
void fc_free_seg_command_line(t_info *info);
int fc_quotes(t_info *info);
int fc_check_variable(t_info *info);
void fc_variable_command(t_info *info);

void fc_test(char **envp);

#endif