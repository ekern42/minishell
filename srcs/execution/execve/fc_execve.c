/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/15 13:23:48 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_execve(t_info *info, int i)
{
	info->exe->path = fc_path_for_execve(info, i);
	info->exe->cmds_execve = info->exe->cmds[i];
	 if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		return (fc_putstr_fd_error("error: ", info));
	return (1);
}
