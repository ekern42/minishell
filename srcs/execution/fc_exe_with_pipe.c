/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:06:00 by angelo            #+#    #+#             */
/*   Updated: 2022/10/02 11:43:42 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_exe_with_pipe(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(6, "Problem with pipe(info->exe->fd)\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_init\n");

	if (info->exe->pid_init == 0)
	{
		fc_stdin_to_stdout(info);
		info->idx = 0;
		fc_builtins_or_execve(info);
	}
	info->exe->pid_other = fork();
	if (info->exe->pid_other < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_other\n");
	if (info->exe->pid_other == 0)
	{
		fc_stdout_to_stdin(info);
		info->idx = 0;
		info->idx2 = 1;
		fc_builtins_or_execve(info);
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


/*
int	fc_exe_with_pipe(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(6, "Problem with pipe(info->exe->fd)\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_init\n");

	if (info->exe->pid_init == 0)
	{
		fc_stdin_to_stdout(info);
		info->idx = 0;
		fc_builtins_or_execve(info);
		//execve(info->path, info->exe->cmds[info->idx2], NULL);
	}
	//info->idx2 = 1;
	info->exe->pid_other = fork();
	if (info->exe->pid_other < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_other\n");
	if (info->exe->pid_other == 0)
	{
		fc_stdout_to_stdin(info);
		info->idx = 0; 
		//while (fc_path_for_execve(info) == NULL) // Pourquoi le while n'est plus nécessaire ???
		//	info->idx++;
		info->idx2 = 1;
		//info->path = fc_path_for_execve(info);
		fc_builtins_or_execve(info);
		//execve(info->path, info->exe->cmds[info->idx2], NULL);
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
*/