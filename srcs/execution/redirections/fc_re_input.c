/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 18:26:02 by ekern             #+#    #+#             */
/*   Updated: 2022/10/14 19:21:13 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_re_input(t_info *info, int a, int i)
{
	int	fd;

	if (ft_strncmp(info->exe->cmds[i][a], "<", 2) == 0)
	{
		fd = open(info->exe->cmds[i][a + 1], O_RDONLY);
		if (fd == -1)
			fc_error_exe(1, "open");
		if (dup2(fd, STDIN_FILENO) == -1)
			fc_error_exe(1, "dup2");
		if (close(fd) == -1)
			fc_error_exe(1, "close");
		info->exe->cmds[i][a] = NULL;
		info->exe->path = fc_path_for_execve(info, i);
		//fc_execve(info, i, "stdin");
		//fc_builtins_or_execve(info, i, "stdin");
		fc_builtins_or_execve(info, i);
		return (1);
	}
	return (0);
}
