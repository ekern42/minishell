/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:13:57 by ekern             #+#    #+#             */
/*   Updated: 2022/09/30 12:28:36 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_builtins(t_info *info)
{
	if (strncmp(info->seg_command_line[info->idx], "echo", 5) == 0)
		fc_echo(info);
	else if (strncmp(info->seg_command_line[info->idx], "cd", 3) == 0)
		fc_cd(info);
	else if (strncmp(info->seg_command_line[info->idx], "pwd", 4) == 0)
		fc_pwd(info);
	else if (strncmp(info->seg_command_line[info->idx], "export", 7) == 0)
		fc_export(info);
	else if (strncmp(info->seg_command_line[info->idx], "unset", 6) == 0)
		fc_unset(info);
	else if (strncmp(info->seg_command_line[info->idx], "env", 4) == 0)
		fc_env(info);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	exit (0);
}
