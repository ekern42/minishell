/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_not_in_last_command.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:37:31 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 19:12:10 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_not_in_last_command(t_info *info, int i)
{
	int		a;
	bool	bool_temp;

	a = 0;
	bool_temp = false;
	if (pipe(info->exe->fd) == -1)
		fc_error_exe(1, "pipe");
	//info->pid = fork();
	//if (info->pid == 0)
//	{
		/*while (info->exe->cmds[i][a] != NULL && bool_temp == false)
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
		}*/
		/*if (bool_temp == false)
		{
			fc_stdin_to_stdout(info);
			info->exe->path = fc_path_for_execve(info, i);
			fc_builtins_or_execve(info, i, "stdout");
		}*/
		if (bool_temp == false)
		{
			/*if (fc_is_builtin(info, i))
				fc_stdin_to_stdout(info);
			else
				info->exe->tmp_fd = info->exe->fd[1];
			info->exe->path = fc_path_for_execve(info, i);
			fc_builtins_or_execve(info, i, "stdout");*/
			fc_stdin_to_stdout(info);
			info->exe->path = fc_path_for_execve(info, i);
			//fc_execve(info, i, "stdout");
		}
		
//	}
	else
	{
		// close(info->exe->fd[0]);
		// close(info->exe->fd[1]); 
		if (wait(NULL) == -1)
			fc_error_exe(1, "wait");
		if (close(info->exe->fd[1]) == -1)
			fc_error_exe(1, "close");
		if (close(info->exe->tmp_fd) == -1)
			fc_error_exe(1, "close");
		info->exe->tmp_fd = info->exe->fd[0];
	}
	return (0);
}
