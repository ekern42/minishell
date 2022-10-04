/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_output.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:48:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/03 10:22:02 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// >
int	fc_re_output(t_info *info)
{
	(void)info;
	return (0);
}

/*

//fc_create_left_str(info);
//fc_print_str_left(info);
//printf("%s\n", info->exe->cmds[0][0]);
//printf("%s\n", info->exe->cmds[0][1]);
//printf("%s\n", info->exe->cmds[0][2]);
//printf("%s\n", info->exe->cmds[0][3]);

//printf("%s\n", info->exe->cmds[1][0]); // segfault
//printf("%s\n", info->exe->cmds[1][1]); // segfault
int	fc_re_append(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(1, "Problem with fork\n");
	if (info->exe->pid_init == 0)
	{
		fc_stdin_to_stdout(info);
		info->idx = 0;
		info->idx2 = 0;
		fc_builtins_or_execve(info);
	}
	
	info->exe->buffer = malloc(sizeof(char) * 1000);
	if (read(info->exe->fd[0], info->exe->buffer, 999) < 0)
		fc_error_tmp(1, "Problem with read\n");

	info->idx = 1;
	info->idx2 = 0;
	while (fc_path_for_execve(info) == NULL)
		info->idx++;
	
	info->exe->fd[0] = open(info->exe->cmds[info->idx2][info->idx], O_CREAT | O_RDWR, 0777);
	if (info->exe->fd[0] < 0)
		fc_error_tmp(1, "Problem with open\n");
	
	if (write(info->exe->fd[0], info->exe->buffer, ft_strlen(info->exe->buffer)) < 0)
		fc_error_tmp(1, "Problem with write\n");

	if (close (info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	if (waitpid(info->exe->pid_init, NULL, 0) < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->pid_init\n");
	
	return (0);
}
*/