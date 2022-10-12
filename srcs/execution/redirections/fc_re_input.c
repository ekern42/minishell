/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:26:02 by ekern             #+#    #+#             */
/*   Updated: 2022/10/12 13:26:01 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_re_input(t_info *info, int a, int i)
{
	int    fd;

	if (ft_strncmp(info->exe->cmds[i][a], "<", 2) == 0)
	{
		fd = open(info->exe->cmds[i][a + 1], O_RDONLY);
		if (fd == -1)
			fc_error_tmp(1, "open");
		if (dup2(fd, STDIN_FILENO) == -1)	
			fc_error_tmp(1, "dup2");
		if (close(fd) == -1)
			fc_error_tmp(1, "close");
		info->exe->cmds[i][a] = NULL;
		info->exe->path = fc_path_mlt_pipes(info, i);
		fc_execve_re(info, i, "stdin");
		return (1);
	}
	return (0);
}
