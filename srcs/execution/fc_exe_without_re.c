/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_without_re.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:43:02 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 16:17:27 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fc_init_exe_without_re(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(3, "Problem with pipe(info->exe->fd)\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(4, "Problem with info->exe->pid_init\n");
	return (0);
}

int	fc_exe_without_re(t_info *info)
{
	fc_init_exe_without_re(info);
	if (info->exe->pid_init == 0)
	{
		info->idx = 0;
		fc_builtins_or_execve(info);
	}
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(5, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(5, "Problem with close(info->exe->fd[1])\n");
	if (waitpid(info->exe->pid_init, WIFEXITED(true), 0) < 0)
		fc_error_tmp(6, "Problem with waitpid - info->exe->pid_init\n");
	return (0);
}

//if (fc_builtins(info) != 0 || fc_execution_cmd(info) != 0)
//{
//	ft_putstr_fd("error : command not found\n", 1);
//	fc_free_seg_command_line(info);
//}
