/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtins_or_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:22:07 by angelo            #+#    #+#             */
/*   Updated: 2022/09/19 20:26:15 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_builtins_or_execve(t_info *info)
{
	if ((strncmp(info->seg_command_line[0], "echo", 5) == 0)
		//|| (strncmp(info->seg_command_line[0], "pwd", 4) == 0)
		|| (strncmp(info->seg_command_line[0], "cd", 3) == 0)
		|| (strncmp(info->seg_command_line[0], "exit", 5) == 0)
		|| (strncmp(info->seg_command_line[0], "env", 4) == 0)
		|| (strncmp(info->seg_command_line[0], "export", 7) == 0)
		|| (strncmp(info->seg_command_line[0], "unset", 6) == 0))
		fc_builtins(info);
	else
		fc_execve(info);
	return (2);
}
