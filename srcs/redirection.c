/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/18 16:07:30 by gudias            #+#    #+#             */
/*   Updated: 2023/03/17 12:35:19 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	redirect_input(int new_fd)
{	
	dup2(new_fd, 0);
}

static void	redirect_output(int new_fd)
{
	dup2(new_fd, 1);
}

void	set_redirections(t_cmd *cmd)
{
	if (cmd->fd_in > 0)
		redirect_input(cmd->fd_in);
	if (cmd->fd_out > 1)
		redirect_output(cmd->fd_out);
}

void	get_redirections(t_vars *vars, t_cmd *cmd)
{	
	cmd->fd_in = get_segment_fd_in(vars, cmd->args);
	cmd->fd_out = get_segment_fd_out(cmd->args);
	clear_chevron_segment(cmd->args);
}

void	reset_redirections(t_vars *vars, t_cmd *cmd)
{
	if (cmd->fd_in > 0)
		close (cmd->fd_in);
	if (cmd->fd_out > 1)
	{
		redirect_output(vars->stdout_fd);
		close (cmd->fd_out);
	}
}
