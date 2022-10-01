/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtins_or_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:22:07 by angelo            #+#    #+#             */
/*   Updated: 2022/09/27 13:48:47 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_builtins_or_execve(t_info *info)
{
	if ((strncmp(info->seg_command_line[info->idx], "echo", 5) == 0)
		|| (strncmp(info->seg_command_line[info->idx], "pwd", 4) == 0)
		|| (strncmp(info->seg_command_line[info->idx], "cd", 3) == 0)
		|| (strncmp(info->seg_command_line[info->idx], "exit", 5) == 0)
		|| (strncmp(info->seg_command_line[info->idx], "env", 4) == 0)
		|| (strncmp(info->seg_command_line[info->idx], "export", 7) == 0)
		|| (strncmp(info->seg_command_line[info->idx], "unset", 6) == 0))
		fc_builtins(info);
	else
		fc_execve(info);
	return (1);
}
