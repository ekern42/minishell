/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit_re.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/16 12:24:31 by aprosper          #+#    #+#             */
/*   Updated: 2022/10/16 12:55:57 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit_re_with_re_input(t_info *info, int i)
{
	info->b->fd_ex = 0;
	if (ft_strncmp(info->exe->cmds[i][0], "exit", 5) == 0
		&& ft_strncmp(info->exe->cmds[i][1], "<", 2) == 0)
	{
		if (info->exe->cmds[i][2] == NULL)
			return (-2);
		info->b->fd_ex = open(info->exe->cmds[i][2], O_WRONLY);
		if (info->b->fd_ex > 0)
		{
			if (close(info->b->fd_ex) == -1)
				fc_error_exe(1, "close");
			return (info->b->fd_ex);
		}
		else if (info->exe->cmds[i][2] != NULL && info->b->fd_ex == -1)
			return (-1);
	}
	return (0);
}

int	fc_exit_re_with_re(t_info *info, int i)
{
	info->b->fd_ex = 0;
	if (ft_strncmp(info->exe->cmds[i][0], "exit", 5) == 0)
	{
		if (ft_strncmp(info->exe->cmds[i][1], ">>", 3) == 0)
		{
			info->b->fd_ex = open(info->exe->cmds[i][2],
				O_WRONLY | O_CREAT | O_APPEND, 0644);
			if (info->b->fd_ex == -1)
				fc_error_exe(1, "open");
			if (close(info->b->fd_ex) == -1)
				fc_error_exe(1, "close");
			return (info->b->fd_ex);
		}
		else if	(ft_strncmp(info->exe->cmds[i][1], ">", 2) == 0)
		{
			info->b->fd_ex = open(info->exe->cmds[i][2],
				O_WRONLY | O_CREAT | O_TRUNC, 0644);
			if (info->b->fd_ex == -1)
				fc_error_exe(1, "open");
			if (close(info->b->fd_ex) == -1)
				fc_error_exe(1, "close");
			return (info->b->fd_ex);
		}
	}
	return (0);
}

int	fc_exit_re(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
	{
		fc_exit_re_with_re(info, i);
		fc_exit_re_with_re_input(info, i);
		info->b->local_fd = STDOUT_FILENO;
		exit(127);
	}
	else
	{
		fc_exit_re_with_re(info, i);
		fc_exit_re_with_re_input(info, i);
		info->b->local_fd = STDOUT_FILENO;
		exit (127);
	}
	return (1);
}
