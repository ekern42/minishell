/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/04 11:48:23 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_execve_mlt_pipes(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_for_execve(info);
	info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx2][info->idx];
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve\n");
	return (0);
}

int	fc_execve(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_for_execve(info);
	info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx2][info->idx];
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve\n");
	return (0);
}


int	fc_execve_redir(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_for_execve(info);
	info->exe->cmds_execve = fc_create_left_str(info);
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve_redir\n");
	return (0);
}
