/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 16:22:27 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_execve(t_info *info, int i)
{
	info->exe->path = fc_path_for_execve(info, i);
	info->exe->cmds_exe = info->exe->cmds[i];
	info->exe->envp_exe = (char **)info->envp;
	 if (execve(info->exe->path, info->exe->cmds_exe, info->exe->envp_exe) == -1)
		return (fc_putstr_fd_error("error: ", info));
	return (1);
}
