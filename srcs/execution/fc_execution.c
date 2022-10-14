/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 19:36:27 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_execution(t_info *info)
{
	int	i;

	i = -1;
	while (info->exe->cmds[++i] != NULL)
	{
		if (pipe(info->exe->fd) == -1)
			fc_error_exe(1, "pipe");
		info->exe->pid = fork();
		if (info->exe->pid == -1)
			fc_error_exe(1, "fork");
		else if (info->exe->pid == 0)
		{
			if (dup2(info->exe->tmp_fd, STDIN_FILENO) == -1)
				fc_error_exe(1, "dup2");
			if (info->exe->cmds[i + 1] != NULL)
			{
				if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
					fc_error_exe(1, "dup2");
			}
			if (close(info->exe->fd[0]) == -1)
				fc_error_exe(1, "close");
			fc_builtins_or_execve(info, i);
		}
		else
		{
			if (waitpid(info->exe->pid, NULL, 0) == -1)
				fc_error_exe(1, "waitpid");
			if (close(info->exe->fd[1]) == -1)
				fc_error_exe(1, "close");
			info->exe->tmp_fd = info->exe->fd[0];
		}
	}
	return (0);
}

