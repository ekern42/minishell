/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 13:13:57 by ekern             #+#    #+#             */
/*   Updated: 2022/09/06 15:49:51 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_builtins(t_info *info)
{
	if (strncmp(info->seg_command_line[0], "echo", 5) == 0)
		fc_echo(info);
	else if (strncmp(info->seg_command_line[0], "cd", 3) == 0)
		ft_putstr_fd("cd\n", 1);
	else if (strncmp(info->seg_command_line[0], "pwd", 4) == 0)
		ft_putstr_fd("pwd\n", 1);
	else if (strncmp(info->seg_command_line[0], "export", 7) == 0)
		ft_putstr_fd("export\n", 1);
	else if (strncmp(info->seg_command_line[0], "unset", 6) == 0)
		ft_putstr_fd("unset\n", 1);
	else if (strncmp(info->seg_command_line[0], "env", 4) == 0)
		ft_putstr_fd("env\n", 1);
	else if (strncmp(info->seg_command_line[0], "exit", 5) == 0)
		fc_exit(info);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	else
		ft_putstr_fd("error : command not found\n", 1);
	fc_free_seg_command_line(info);
	return (0);
}
