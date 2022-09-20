/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/09/19 20:38:16 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../../minishell.h"

int	fc_execve(t_info *info)
{
	info->path = fc_path_for_execve(info);
	if ((execve(info->path, fc_cpy_cmd(info),
			(char **)info->envp)) == -1)
		fc_error_exe2(4);
	free (info->path);
	return (0);
}

/*
int	fc_execve(t_info *info)
{
	info->path = fc_path_for_execve(info);
	info->cpy_cmd = fc_cpy_cmd(info);
	
	//info->idx_seg_cmd_line = 0;
	if ((execve(info->path, info->cpy_cmd,
			(char **)info->envp)) == -1)
		fc_error_exe2(4);
	free (info->path);
	return (0);
}
*/

/*
int	fc_execution_cmd(t_info *info)
{
	if ((execve(fc_find_path_cmd(info),
				(char **)&info->seg_command_line[info->idx_seg_cmd_line],
				(char **)info->envp)) == -1)
		fc_error_exe2(200);
	return (0);
}
*/
