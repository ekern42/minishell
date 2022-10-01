/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/10/01 18:34:01 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fc_init_execution(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(3, "Problem with pipe(info->exe->fd)\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(4, "Problem with info->exe->pid_init\n");
	return (0);
}

// idx2 est relié au pipe
int	fc_execution(t_info *info)
{
	fc_init_execution(info);
	if (info->exe->pid_init == 0)
	{
		info->idx = 0;
		fc_builtins_or_execve(info);
	}
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(5, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(5, "Problem with close(info->exe->fd[1])\n");

	if (waitpid(info->exe->pid_init, NULL, 0) < 0)
		fc_error_tmp(6, "Problem with waitpid - info->exe->pid_init\n");

	return (0);
}

//if (fc_builtins(info) != 0 || fc_execution_cmd(info) != 0)
//{
//	ft_putstr_fd("error : command not found\n", 1);
//	fc_free_seg_command_line(info);
//}
