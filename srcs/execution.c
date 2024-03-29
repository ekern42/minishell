/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/22 15:29:38 by gudias            #+#    #+#             */
/*   Updated: 2023/03/17 11:51:10 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_cmd(t_vars *vars, t_cmd *cmd, int i)
{
	int		return_code;

	return_code = 0;
	set_redirections(cmd);
	translate_dollars_all(cmd->args, vars);
	if (cmd->args[i] && vars->segments_count == 1 && is_builtin(cmd->args[i]))
		return_code = exec_builtin(vars, (cmd->args) + i);
	else
		return_code = run_cmd(vars, cmd, i);
	return (return_code);
}
