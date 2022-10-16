/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:48:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 15:34:55 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_re_output(t_info *info, int i, int j, int fd)
{
	info->exe->fd_re = fd;
	info->exe->fd_re = open(info->exe->cmds[i][j + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (info->exe->fd_re == -1)
		fc_error_exe(1, "open");
	if (dup2(info->exe->fd_re, STDOUT_FILENO) == -1)
		fc_error_exe(1, "dup2");
	if (close(info->exe->fd_re) == -1)
		fc_error_exe(1, "close");
	info->exe->cmds[i][j] = NULL;
	if (info->exe->cmds[i + 1] != NULL)
		info->exe->fd[1] = info->exe->fd_re;
	info->exe->is_re = 1;
	return (0);
}
