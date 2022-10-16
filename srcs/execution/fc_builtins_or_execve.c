/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtins_or_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:22:07 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 17:08:43 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	fc_builtins(t_info *info, int i, int j)
{
	if (ft_strncmp(info->exe->cmds[i][j], "echo", 5) == 0)
		fc_echo(info, i, j);
	else if (ft_strncmp(info->exe->cmds[i][j], "cd", 3) == 0)
		fc_cd(info);
	else if (ft_strncmp(info->exe->cmds[i][j], "exit", 5) == 0)
		fc_exit_re(info, i);
	else if (ft_strncmp(info->exe->cmds[i][j], "pwd", 4) == 0)
		fc_pwd(info, i);
	else if (ft_strncmp(info->exe->cmds[i][j], "export", 7) == 0)
		fc_export(info);
	else if (ft_strncmp(info->exe->cmds[i][j], "unset", 6) == 0)
		fc_unset(info);
	else if (ft_strncmp(info->exe->cmds[i][j], "env", 4) == 0)
		fc_env(info, i);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	return (1);
}
*/

/*
int	fc_builtins_or_execve(t_info *info, int i)
{
	int	j;

	j = -1;
	while (info->exe->cmds[i][++j] != NULL)
	{
		if (fc_builtins(info, i, j) != 1)
			fc_builtins(info, i, j);
		else
			fc_execve(info, i);
	}
	return (0);
}
*/

int	fc_builtins(t_info *info, int i)
{
	if (ft_strncmp(*info->exe->cmds[i], "echo", 5) == 0)
		fc_echo(info, i);
	else if (ft_strncmp(*info->exe->cmds[i], "cd", 3) == 0)
		fc_cd(info);
	else if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
		fc_exit_re(info, i);
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

int	fc_builtins_or_execve(t_info *info, int i)
{
	if (fc_builtins(info, i) != 1)
		fc_builtins(info, i);
	else
		fc_execve(info, i);
	return (0);
}

// > test1 ls > test2