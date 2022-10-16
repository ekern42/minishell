/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:34 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 12:52:49 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit_m_with_re_input(t_info *info)
{
	info->b->fd_ex = 0;
	if (ft_strncmp(info->exe->cmds[0][0], "exit", 5) == 0
		&& ft_strncmp(info->exe->cmds[0][1], "<", 2) == 0)
	{
		if (info->exe->cmds[0][2] == NULL)
			return (-2);
		info->b->fd_ex = open(info->exe->cmds[0][2], O_WRONLY);
		if (info->b->fd_ex > 0)
		{
			if (close(info->b->fd_ex) == -1)
				fc_error_exe(1, "close");
			return (info->b->fd_ex);
		}
		else if (info->exe->cmds[0][2] != NULL && info->b->fd_ex == -1)
			return (-1);
	}
	return (0);
}

int	fc_exit_m_with_re(t_info *info)
{
	info->b->fd_ex = 0;
	if (ft_strncmp(info->exe->cmds[0][0], "exit", 5) == 0)
	{
		if (ft_strncmp(info->exe->cmds[0][1], ">", 2) == 0)
			info->b->fd_ex = open(info->exe->cmds[0][2],
					O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else if (ft_strncmp(info->exe->cmds[0][1], ">>", 3) == 0)
			info->b->fd_ex = open(info->exe->cmds[0][2],
					O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (info->exe->cmds[0][2] == NULL)
				return (-2);
		else if (info->exe->cmds[0][2] != NULL)
		{
			if (info->b->fd_ex == -1)
				fc_error_exe(1, "open");
			if (close(info->b->fd_ex) == -1)
				fc_error_exe(1, "close");
			return (info->b->fd_ex);
		}
	}
	return (0);
}

int	fc_exit_m(t_info *info)
{
	if (ft_strncmp(info->exe->cmds[0][0], "exit", 5) == 0
		&& info->lex->pipes == false)
	{
		if (info->exe->cmds[0][1] == NULL
			|| fc_exit_m_with_re(info) > 0
			|| fc_exit_m_with_re_input(info) > 0)
		{
			write(1, "exit\n", 5);
			fc_final_free(info);
			exit (127);
		}
		else if (fc_exit_m_with_re(info) == -1
			|| fc_exit_m_with_re_input(info) == -1)
		{
			fc_error_message(info, 1);
			return (EXIT_FAILURE);
		}
		else if (fc_exit_m_with_re(info) == -2
			|| fc_exit_m_with_re_input(info) == -2)
		{
			fc_error_message(info, 2);
			return (EXIT_FAILURE);
		}
	}
	return (1);
}
