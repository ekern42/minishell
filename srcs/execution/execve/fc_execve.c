/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/12 11:15:01 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_execve_re(t_info *info, int i, char *std)
{
	if (ft_strncmp(std, "stdin", 6) == 0)
	{
		if (dup2(info->exe->tmp_fd, STDOUT_FILENO) == -1)
			fc_error_tmp(1, "dup2");
	}
	else if (ft_strncmp(std, "stdout", 7) == 0)
	{
		if (dup2(info->exe->tmp_fd, STDIN_FILENO) == -1)
			fc_error_tmp(1, "dup2");
	}
	else
		return (1);
	if (close(info->exe->tmp_fd) == -1)
		fc_error_tmp(1, "close");
	info->exe->cmds_execve = info->exe->cmds[i];
	//info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx_re][i]; // ???
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		return (fc_putstr_fd_re("error: ", info));
	return (1);
}


int	fc_execve(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_for_execve(info);
	info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx_re][info->idx];
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve\n");
	return (0);
}


int	fc_execve_redir(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_for_execve(info);
	info->exe->cmds_execve = fc_create_left_str(info);
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve_redir\n");
	return (0);
}

// A supprimer
int	fc_execve_mlt_pipes(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_mlt_pipes(info, info->idx_re);
	//info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx_re][info->idx];
	info->exe->cmds_execve = fc_create_tmp_str(info);
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve\n");
	return (0);
}
