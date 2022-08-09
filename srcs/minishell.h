/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:57 by ekern             #+#    #+#             */
/*   Updated: 2022/08/09 17:21:18 by ekern            ###   ########.fr       */
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
typedef struct	s_info
{
	char	*command_line;
}				t_info;
/* SRCS */

void fc_error(int a);
size_t	fc_strlen(const char *str);
int	fc_signal(t_info *info);
void fc_control_d(void);
int	fc_init(t_info *info);

#endif