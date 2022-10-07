/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_builtins_or_execve.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:22:07 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 16:37:22 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_builtins_or_execve(t_info *info)
{
	if ((strncmp(info->exe->cmds[info->idx_re][info->idx], "echo", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "pwd", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "cd", 3) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "exit", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "env", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "export", 7) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "unset", 6) == 0))
		fc_builtins(info);
	else if (fc_check_is_redir(info) == 1 && info->lex->pipes == false) // aucune redirection
		fc_execve(info);
	else if (info->lex->pipes == true)
		fc_execve_mlt_pipes(info);
	else if (info->lex->re_append == true && info->lex->pipes == false) // juste pour exécuter >>
		fc_execve_redir(info);
	return (1);
}


int	fc_builtins_or_execve2(t_info *info, int i)
{
	if ((strncmp(info->exe->cmds[info->idx_re][info->idx], "echo", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "pwd", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "cd", 3) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "exit", 5) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "env", 4) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "export", 7) == 0)
		|| (strncmp(info->exe->cmds[info->idx_re][info->idx], "unset", 6) == 0))
		fc_builtins(info);
	else
		fc_execve_re(info, i);
	return (1);
}
