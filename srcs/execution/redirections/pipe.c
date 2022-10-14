/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:36:10 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 14:51:59 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// Donc à gauche du pipe
int	fc_stdin_to_stdout(t_info *info)
{
	//close(info->exe->fd[0]);
	if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
		fc_error_exe(1, "dup2 in to out");
	if (close(info->exe->fd[1]) == -1)
		fc_error_exe(1, "close in to out");
	if (close(info->exe->fd[0]) == -1)
		fc_error_exe(1, "close");
	return (0);
}

// Donc à droite du pipe
int	fc_stdout_to_stdin(t_info *info)
{
	if (dup2(info->exe->fd[0], STDIN_FILENO) < 0)
		fc_error_exe(1, "Problem with dup2 - info->exe->fd[0], STDIN_FILENO\n");
	if (close(info->exe->fd[0]) < 0)
		fc_error_exe(1, "Problem with close - fd[0] - fc_stdout_to_stdin\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_exe(1, "Problem with close - fd[1]- fc_stdout_to_stdin\n");
	return (0);
}
