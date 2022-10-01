/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:06:00 by angelo            #+#    #+#             */
/*   Updated: 2022/10/01 12:34:21 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"


int	fc_exe_with_pipe(t_info *info)
{
	//fc_print_seg_cmd_line2(info);
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(6, "Problem with pipe(info->exe->fd)\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_init\n");

	if (info->exe->pid_init == 0)
	{
		fc_create_left_str(info);
		fc_stdin_to_stdout(info);
		info->idx = 0;
		info->path = NULL;
		while (fc_path_for_execve(info) == NULL)
			info->idx++;
		//printf("idx = %d\n", info->idx); // comment voir puisque ça a été redirigé ??
		info->path = fc_path_for_execve(info);
		//execve(info->path, fc_create_left_str(info), NULL);
		info->idx = 0;
		execve(info->path, info->exe->cmds[info->idx], NULL);
	}

	info->exe->pid_other = fork();
	if (info->exe->pid_other < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_other\n");
	if (info->exe->pid_other == 0)
	{
		fc_create_right_str(info);
		fc_stdout_to_stdin(info);
		info->idx = 1;
		info->path = NULL;
		while (fc_path_for_execve(info) == NULL)
			info->idx++;
		info->path = fc_path_for_execve(info);
		//printf("info->path = %s\n", info->path);
		//execve(info->path, fc_create_right_str(info), NULL);
		execve(info->path, info->exe->cmds[info->idx], NULL);
	}
	
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[1])\n");

	if (waitpid(info->exe->pid_init, NULL, 0) < 0)
		fc_error_tmp(5, "Problem with waitpid - info->exe->pid_init\n");
	if (waitpid(info->exe->pid_other, NULL, 0) < 0)
		fc_error_tmp(5, "Problem with waitpid - info->exe->pid_other\n");

	return (0);
}