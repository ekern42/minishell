/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtins_or_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:22:07 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 19:52:46 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_builtins(t_info *info, int i)
{
	if (strncmp(info->exe->cmds[info->idx_re][i], "echo", 5) == 0)
		fc_echo(info);
	else if (strncmp(info->exe->cmds[info->idx_re][i], "cd", 3) == 0)
		fc_cd(info);
	else if (strncmp(info->exe->cmds[info->idx_re][i], "pwd", 4) == 0)
		fc_pwd(info);
	else if (strncmp(info->exe->cmds[info->idx_re][i], "export", 7) == 0)
		fc_export(info);
	else if (strncmp(info->exe->cmds[info->idx_re][i], "unset", 6) == 0)
		fc_unset(info);
	else if (strncmp(info->exe->cmds[info->idx_re][i], "env", 4) == 0)
		fc_env(info);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	return (1);
}

int	fc_is_builtin(t_info *info, int i)
{
	if ((strncmp(info->exe->cmds[info->idx_re][i], "echo", 5) == 0)
	|| (strncmp(info->exe->cmds[info->idx_re][i], "pwd", 4) == 0)
	|| (strncmp(info->exe->cmds[info->idx_re][i], "cd", 3) == 0)
	|| (strncmp(info->exe->cmds[info->idx_re][i], "exit", 5) == 0)
	|| (strncmp(info->exe->cmds[info->idx_re][i], "env", 4) == 0)
	|| (strncmp(info->exe->cmds[info->idx_re][i], "export", 7) == 0)
	|| (strncmp(info->exe->cmds[info->idx_re][i], "unset", 6) == 0))
		return (0);
	return (1);
}

int	fc_builtins_or_execve(t_info *info, int i)
{
	if (fc_is_builtin(info, i) == 0)
		fc_builtins(info, i);
	else if (fc_is_builtin(info, i) == 1)
		fc_execve_re(info, i);
	return (0);
}


/*
int	fc_builtins_or_execve(t_info *info, int i)
{
	if ((strncmp(info->exe->cmds[info->idx_re][i], "echo", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][i], "pwd", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][i], "cd", 3) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][i], "exit", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][i], "env", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][i], "export", 7) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][i], "unset", 6) == 0))
		fc_builtins(info, i);
	else
		fc_execve_re(info, i);
	return (1);
}
*/

int	fc_builtins2(t_info *info)
{
	if (strncmp(info->exe->cmds[info->idx_re][info->idx], "echo", 5) == 0)
		fc_echo(info);
	else if (strncmp(info->exe->cmds[info->idx_re][info->idx], "cd", 3) == 0)
		fc_cd(info);
	else if (strncmp(info->exe->cmds[info->idx_re][info->idx], "pwd", 4) == 0)
		fc_pwd(info);
	else if (strncmp(info->exe->cmds[info->idx_re][info->idx], "export", 7) == 0)
		fc_export(info);
	else if (strncmp(info->exe->cmds[info->idx_re][info->idx], "unset", 6) == 0)
		fc_unset(info);
	else if (strncmp(info->exe->cmds[info->idx_re][info->idx], "env", 4) == 0)
		fc_env(info);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	return (1);
}

int	fc_builtins_or_execve2(t_info *info)
{
	if ((strncmp(info->exe->cmds[info->idx_re][info->idx], "echo", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "pwd", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "cd", 3) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "exit", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "env", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "export", 7) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "unset", 6) == 0))
		fc_builtins2(info);
	else if (fc_check_is_redir(info) == 1 && info->lex->pipes == false) // aucune redirection
		fc_execve(info);
	else if (info->lex->pipes == true)
		fc_execve_mlt_pipes(info);
	else if (info->lex->re_append == true && info->lex->pipes == false) // juste pour exécuter >>
		fc_execve_redir(info);
	return (1);
}
