/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/02 11:44:36 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_execve(t_info *info)
{
	info->path = fc_path_for_execve(info);
	if ((execve(info->path, (char **)&info->exe->cmds[info->idx2][info->idx],
			(char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with execve\n");
	return (0);
}
