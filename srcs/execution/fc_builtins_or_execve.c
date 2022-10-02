/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtins_or_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:22:07 by angelo            #+#    #+#             */
/*   Updated: 2022/10/02 20:07:06 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_builtins_or_execve(t_info *info)
{
	if ((strncmp(info->exe->cmds[info->idx2][info->idx], "echo", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx2][info->idx], "pwd", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx2][info->idx], "cd", 3) == 0)
		|| (strncmp(info->exe->cmds[info->idx2][info->idx], "exit", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx2][info->idx], "env", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx2][info->idx], "export", 7) == 0)
		|| (strncmp(info->exe->cmds[info->idx2][info->idx], "unset", 6) == 0))
		fc_builtins(info);
	else if (fc_check_is_redir(info) == 1)
		fc_execve(info);
	else if (fc_check_is_redir(info) == 0)
		fc_execve_redir(info);
	return (1);
}
