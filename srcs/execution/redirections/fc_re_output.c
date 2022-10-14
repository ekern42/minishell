/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:48:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 19:21:19 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// >
int	fc_re_output(t_info *info, int a, int i)
{
	int	fd;

	if (ft_strncmp(info->exe->cmds[i][a], ">", 2) == 0)
	{
		fd = open(info->exe->cmds[i][a + 1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (fd == -1)
			fc_error_exe(1, "open");
		if (dup2(fd, STDOUT_FILENO) == -1)
			fc_error_exe(1, "dup2");
		if (close(fd) == -1)
			fc_error_exe(1, "close");
		info->exe->cmds[i][a] = NULL;
		info->exe->path = fc_path_for_execve(info, i);
		//fc_execve(info, i, "stdout");
		//fc_builtins_or_execve(info, i, "stdout");
		fc_builtins_or_execve(info, i);
		return (1);
	}
	return (0);
}
