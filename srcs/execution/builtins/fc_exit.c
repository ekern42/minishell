/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:34 by angelo            #+#    #+#             */
/*   Updated: 2022/10/15 18:40:15 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit_with_re(t_info *info)
{
	int	fd;

	fd = 0;
	if (ft_strncmp(info->exe->cmds[0][0], "exit", 5) == 0
		&& (ft_strncmp(info->exe->cmds[0][1], ">", 2) == 0
		|| ft_strncmp(info->exe->cmds[0][1], ">>", 3) == 0))
	{
		if (info->exe->cmds[0][2] == NULL)
		{
			ft_putstr_fd("Minishell: syntax error", 2);
			ft_putstr_fd("near unexpected token `newline'\n", 2);
			fc_final_free(info);
			exit (1);
		}
		else
		{
			fd = open(info->exe->cmds[0][2], O_WRONLY
					| O_CREAT | O_TRUNC, 0644);
			if (fd == -1)
				fc_error_exe(1, "open");
			if (close(fd) == -1)
				fc_error_exe(1, "close");
		}
	}
	return (fd);
}

int	fc_exit_m(t_info *info)
{
	if ((ft_strncmp(info->exe->cmds[0][0], "exit", 5) == 0)
		&& info->exe->cmds[0][1] == NULL)
	{
		write(1, "exit\n", 5);
		fc_final_free(info);
		exit (127);
	}
	else if ((ft_strncmp(info->exe->cmds[0][0], "exit", 5) == 0)
		&& fc_exit_with_re(info) > 0)
	{
		write(1, "exit\n", 5);
		fc_final_free(info);
		exit (127);
	}
	else
		return (0);
	return (1);
}

/*
int	fc_exit_m(t_info *info)
{
	if (ft_strncmp(*info->exe->cmds[0], "exit", 5) == 0)
	{
		fc_exit_with_re(info);
		write(1, "exit\n", 5);
		fc_final_free(info);
		exit (127);
	}
	return (1);
}
*/

int	fc_exit(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
	{
		info->b->local_fd = STDOUT_FILENO;
		exit(127);
	}
	else
	{
		info->b->local_fd = STDOUT_FILENO;
		exit (127);
	}
	return (1);
}
