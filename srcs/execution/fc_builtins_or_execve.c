/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtins_or_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:22:07 by angelo            #+#    #+#             */
/*   Updated: 2022/10/13 18:16:42 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_builtins(t_info *info, int i)
{
	if (ft_strncmp(*info->exe->cmds[i], "echo", 5) == 0)
		fc_echo(info, i);
	else if (ft_strncmp(*info->exe->cmds[i], "cd", 3) == 0)
		fc_cd(info);
	//else if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0) // ??
	//	fc_exit(info);
	else if (ft_strncmp(*info->exe->cmds[i], "pwd", 4) == 0)
		fc_pwd(info, i);
	else if (ft_strncmp(*info->exe->cmds[i], "export", 7) == 0)
		fc_export(info);
	else if (ft_strncmp(*info->exe->cmds[i], "unset", 6) == 0)
		fc_unset(info);
	else if (ft_strncmp(*info->exe->cmds[i], "env", 4) == 0)
		fc_env(info, i);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	return (1);
}

int	fc_is_builtin(t_info *info, int i)
{
	if ((ft_strncmp(*info->exe->cmds[i], "echo", 5) == 0)
	|| (ft_strncmp(*info->exe->cmds[i], "pwd", 4) == 0)
	|| (ft_strncmp(*info->exe->cmds[i], "cd", 3) == 0)
	|| (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
	|| (ft_strncmp(*info->exe->cmds[i], "env", 4) == 0)
	|| (ft_strncmp(*info->exe->cmds[i], "export", 7) == 0)
	|| (ft_strncmp(*info->exe->cmds[i], "unset", 6) == 0))
		return (0);
	return (1);
}

int	fc_builtins_or_execve(t_info *info, int i, char *std)
{
	if (fc_is_builtin(info, i) == 0)
		fc_builtins(info, i);
	else
		fc_execve(info, i, std);
	return (0);
}
