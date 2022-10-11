/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:45:37 by angelo            #+#    #+#             */
/*   Updated: 2022/10/11 16:47:35 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_re_append(t_info *info, int a, int i)
{
	int fd;
	
	if (ft_strncmp(info->exe->cmds[i][a], ">>", 3) == 0)
	{
		fd = open(info->exe->cmds[i][a + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (fd == -1)
			fc_error_tmp(1, "open");
		if (dup2(fd, STDOUT_FILENO) == -1)	
			fc_error_tmp(1, "dup2");
		if (close(fd) == -1)
			fc_error_tmp(1, "close");
		info->exe->cmds[i][a] = NULL;
		info->exe->path = fc_path_mlt_pipes(info, i);
		fc_execve_re(info, i);
		return (1);
	}
	return (0);
}
