/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/09/20 14:39:04 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int	fc_init_execution(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_exe2(1);
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_exe("fork", 5);
	return (0);
}


int	fc_execution(t_info *info)
{
	fc_init_execution(info);
	if (info->exe->pid_init == 0)
	{
		if (info->lex->nbr_pipe == 1)
		{
			fc_stdin_to_stdout(info);
			if ((execve(fc_path_for_execve(info), fc_cpy_cmd(info), (char **)info->envp)) == -1)
				fc_error_exe2(4);
		}
		else if (info->lex->nbr_pipe == 0)
			fc_builtins_or_execve(info);
	}
	if (info->lex->nbr_pipe == 1)
	{
		info->exe->pid_other = fork();
		if (info->exe->pid_other < 0)
			fc_error_exe2(6);
		if (info->exe->pid_other == 0)
		{
			fc_stdout_to_stdin(info);
			if ((execve(fc_path_for_execve(info), fc_cpy_cmd2(info), (char **)info->envp)) == -1)
				fc_error_exe2(4);
		}
	}
	if (close(info->exe->fd[0]) < 0)
		fc_error_exe2(7);
	if (close(info->exe->fd[1]) < 0)
		fc_error_exe2(8);

	if (waitpid(info->exe->pid_init, NULL, 0) < 0)
		fc_error_exe2(9);
	if (info->lex->nbr_pipe == 1 && info->exe->pid_other != 0)
	{
		if (waitpid(info->exe->pid_other, NULL, 0) < 0)
		fc_error_exe2(10);
	}

	//free (info->cpy_cmd);
	return (0);
}
//if (fc_builtins(info) != 0 || fc_execution_cmd(info) != 0)
//{
//	ft_putstr_fd("error : command not found\n", 1);
//	fc_free_seg_command_line(info);
//}