/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 17:24:47 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_execution(t_info *info)
{
	pid_t	pid;
	int		i;
	int		fd[2];
	int		tmp_fd;

	i = -1;
	while (info->exe->cmds[++i] != NULL)
	{
		if (pipe(fd) == -1)
			fc_error_exe(1, "pipe");
		pid = fork();
		if (pid == -1)
			fc_error_exe(1, "fork");
		else if (pid == 0)
		{
			if (dup2(tmp_fd, 0) == -1)
				fc_error_exe(1, "dup2");
			if (info->exe->cmds[i + 1] != NULL)
			{
				if (dup2(fd[1], 1) == -1)
					fc_error_exe(1, "dup2");
			}
			if (close(fd[0]) == -1)
				fc_error_exe(1, "close");
			//info->exe->path = NULL;
			info->exe->path = fc_path_for_execve(info, i);
			info->exe->cmds_execve = info->exe->cmds[i];
			if (execve(info->exe->path, info->exe->cmds_execve, NULL) == -1)
					fc_error_exe(1, "execve");
			/*if (i == 0)
			{
				if (execve("/bin/ls", info->exe->cmds_execve, NULL) == -1)
					fc_error_exe(1, "execve");
			}
			else if (i == 1)
			{
				if (execve("/usr/bin/grep", info->exe->cmds_execve, NULL) == -1)
					fc_error_exe(1, "execve");
				
			}
			else if (i == 2)
			{
				if (execve("/usr/bin/wc", info->exe->cmds_execve, NULL) == -1)
					fc_error_exe(1, "execve");
			}*/
		}
		else
		{
			if (wait(NULL) == -1)
				fc_error_exe(1, "wait");
			if (close(fd[1]) == -1)
				fc_error_exe(1, "close");
			tmp_fd = fd[0];
		}
	}
	return (0);
}



/*
int	fc_execution(t_info *info)
{
	pid_t	pid;
	int		i;

	i = -1;
	while (info->exe->cmds[++i] != NULL)
	{
		pipe(info->exe->fd);
		if ((pid = fork()) == -1)
		{
			perror("fork");
			exit(1);
		}
		else if (pid == 0)
		{
			dup2(info->exe->tmp_fd, 0);
			if (info->exe->cmds[i + 1] != NULL)
			{
				dup2(info->exe->fd[1], 1);
			}
			close(info->exe->fd[0]);
			//info->exe->path = NULL;
			info->exe->path = fc_path_for_execve(info, i);
			info->exe->cmds_execve = info->exe->cmds[i];
			execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp);
			exit(1);
			//fc_putstr_fd_error(char *str, t_info *info);
		}
		else
		{
			wait(NULL);
			close(info->exe->fd[1]);
			info->exe->tmp_fd = info->exe->fd[0];
		}
	}
	return (0);
}
*/