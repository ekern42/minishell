/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 14:18:54 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_execve(t_info *info, int i, char *std)
{
	if (ft_strncmp(std, "stdin", 6) == 0)
	{
		if (dup2(info->exe->tmp_fd, STDOUT_FILENO) == -1)
			fc_error_exe(1, "dup2");
	}
	else if (ft_strncmp(std, "stdout", 7) == 0)
	{
		if (dup2(info->exe->tmp_fd, STDIN_FILENO) == -1)
			fc_error_exe(1, "dup2");
	}
	else
		return (1);
	if (close(info->exe->tmp_fd) == -1)
		fc_error_exe(1, "close");
	info->exe->cmds_execve = info->exe->cmds[i];
	if (execve(info->exe->path, info->exe->cmds_execve, NULL) == -1)
		return (fc_putstr_fd_error("error: ", info));
	return (1);
}
