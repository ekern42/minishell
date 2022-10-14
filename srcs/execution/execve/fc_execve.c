/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 19:25:23 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//int	fc_execve(t_info *info, int i, char *std)
int	fc_execve(t_info *info, int i)
{
	/*if (ft_strncmp(std, "stdin", 6) == 0)
	{
		if (dup2(info->exe->tmp_fd, STDOUT_FILENO) == -1)
			//fc_error_exe(1, "dup2 exec");
		if (close(info->exe->tmp_fd) == -1)
			fc_error_exe(1, "close in to out");
	}
	else if (ft_strncmp(std, "stdout", 7) == 0)
	{
		// if (dup2(info->exe->tmp_fd, STDIN_FILENO) == -1)
		// 	fc_error_exe(1, "dup2 exec");
		dup2(info->exe->tmp_fd, STDIN_FILENO);
		close(info->exe->tmp_fd);
	}
	//else
	//	return (1);*/
	// if (close(info->exe->tmp_fd) == -1)
	// 	fc_error_exe(1, "close");
	info->exe->path = fc_path_for_execve(info, i);
	info->exe->cmds_execve = info->exe->cmds[i];
	 if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		return (fc_putstr_fd_error("error: ", info));
	return (1);
}
