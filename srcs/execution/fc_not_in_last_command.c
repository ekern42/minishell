/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_not_in_last_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:37:31 by angelo            #+#    #+#             */
/*   Updated: 2022/10/12 14:52:57 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_not_in_last_command(t_info *info, int i)
{
	int	a;
	bool bool_temp;

	a = 0;
	bool_temp = false;
	if (pipe(info->exe->fd) == -1)
		fc_error_exe(1, "pipe");
	if (fork() == 0)
	{
		while (info->exe->cmds[i][a] != NULL && bool_temp == false)
		{
			if ((fc_re_append(info, a, i)) == 1)	
				bool_temp = true;
			if ((fc_re_output(info, a, i)) == 1)
				bool_temp = true;
			if ((fc_re_input(info, a, i)) == 1)
				info->lex->error = true;
			if ((fc_re_del(info, a, i)) == 1)
				info->lex->error = true;
			a++;
		}
		if (bool_temp == false)
		{	
			info->exe->path = fc_path_for_execve(info, i);
			if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
				fc_error_exe(1, "dup2");
			if (close(info->exe->fd[0]) == -1)
				fc_error_exe(1, "close");
			if (close(info->exe->fd[1]) == -1)
				fc_error_exe(1, "close");
			fc_execve(info, i, "stdout");
		}
	}
	else
	{
		if (wait(NULL) < 0)
			fc_error_exe(1, "wait");
		if (close(info->exe->fd[1]) == -1)
			fc_error_exe(1, "close");
		if (close(info->exe->tmp_fd) == -1)
			fc_error_exe(1, "close");
		info->exe->tmp_fd = info->exe->fd[0];
	}
	return (0);
}
