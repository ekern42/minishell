/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:45:37 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 15:35:17 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
int	fc_re_append(t_info *info, int i, int j, int fd)
{
	int	k;

	k = j;

	while (info->exe->cmds[i][j] != NULL)
	{
		printf("cmds = %s | i = %d | j = %d\n", info->exe->cmds[i][j], i, j);
		info->exe->fd_re = fd;
		info->exe->fd_re = open(info->exe->cmds[i][j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (info->exe->fd_re == -1)
			fc_error_exe(1, "open");
		if (dup2(info->exe->fd_re, STDOUT_FILENO) == -1)
			fc_error_exe(1, "dup2");
		if (close(info->exe->fd_re) == -1)
			fc_error_exe(1, "close");
		info->exe->cmds[i][j] = NULL; // faire attention au leaks sur le reste de la chaine qu on pert potentiellement ici
		if (info->exe->cmds[i + 1] != NULL)
			info->exe->fd[1] = info->exe->fd_re;
		//fc_builtins_or_execve(info, i);
		info->exe->is_re = 1;
		if (ft_strncmp(info->exe->cmds[i][j], "|", 2) != 0)
		{
			printf("j = %d\n", j);
			j++;
		}
		else
		{
			j = k;
			break ;
		}
	}
	return (0);
}
*/

int	fc_re_append(t_info *info, int i, int j, int fd)
{
	info->exe->fd_re = fd;
	info->exe->fd_re = open(info->exe->cmds[i][j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (info->exe->fd_re == -1)
		fc_error_exe(1, "open");
	if (dup2(info->exe->fd_re, STDOUT_FILENO) == -1)
		fc_error_exe(1, "dup2");
	if (close(info->exe->fd_re) == -1)
		fc_error_exe(1, "close");
	info->exe->cmds[i][j] = NULL; // faire attention au leaks sur le reste de la chaine qu on pert potentiellement ici
	if (info->exe->cmds[i + 1] != NULL)
		info->exe->fd[1] = info->exe->fd_re;
	info->exe->is_re = 1;
	return (0);
}
