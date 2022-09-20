/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:13:57 by ekern             #+#    #+#             */
/*   Updated: 2022/09/19 18:38:34 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_builtins(t_info *info)
{
	if (strncmp(info->seg_command_line[0], "echo", 5) == 0)
		fc_echo(info);
	else if (strncmp(info->seg_command_line[0], "cd", 3) == 0)
		fc_cd(info);
	//else if (strncmp(info->seg_command_line[0], "pwd", 4) == 0)
		//fc_pwd(info);
	else if (strncmp(info->seg_command_line[0], "export", 7) == 0)
		fc_export(info);
	else if (strncmp(info->seg_command_line[0], "unset", 6) == 0)
		fc_unset(info);
	else if (strncmp(info->seg_command_line[0], "env", 4) == 0)
		fc_env(info);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	exit (0);
}
