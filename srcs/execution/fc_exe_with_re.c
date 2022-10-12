/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_re.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:44:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/12 13:32:06 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_exe_with_re(t_info *info)
{
	int	i;

	i = 0;
	info->exe->tmp_fd = dup(STDIN_FILENO);
	if (info->exe->tmp_fd == -1)
		fc_error_tmp(1, "dup");
	while (i < info->lex->nbr_pipe + 1)
	{
		//printf("i = %d\n", i);
		if (i == info->lex->nbr_pipe)
			fc_is_last_command(info, i);
		else // envoie l'output dans un pipe
			fc_not_in_last_command(info, i);
		i++;
	}
	if (close(info->exe->tmp_fd) == -1)
		fc_error_tmp(1, "close");
	return (0);
}

int	fc_putstr_fd_re(char *str, t_info *info)
{
	while (*str)
		write(2, str++, 1);
	if (info->exe->path)
		while(*info->exe->path)
			write(2, info->exe->path++, 1);
	write(2, "\n", 1);
	return (1);
}


int	fc_is_last_command(t_info *info, int i)
{
	int	a;

	a = 0;
	if (fork() == 0)
	{	
		while (info->exe->cmds[i][a] != NULL)
		{
			if ((fc_re_append(info, a, i)) == 1)	
				info->lex->error = true;
			if ((fc_re_output(info, a, i)) == 1)
				info->lex->error = true;
			if ((fc_re_input(info, a, i)) == 1)
				info->lex->error = true;
			if ((fc_re_del(info, a, i)) == 1)
				info->lex->error = true;
			a++;
		}
		if (info->lex->error == false)
		{	
			info->exe->path = fc_path_mlt_pipes(info, i);
			fc_execve_re(info, i, "stdout");
			//fc_builtins_or_execve(info, i);
		}
	}
	else
	{
		while(waitpid(-1, NULL, WUNTRACED) != -1)
			;
		if (close(info->exe->tmp_fd) == -1)
			fc_error_tmp(1, "close");
		info->exe->tmp_fd = dup(STDIN_FILENO);
		if (info->exe->tmp_fd == -1)
			fc_error_tmp(1, "dup");
	}
	return (0);
}

int	fc_not_in_last_command(t_info *info, int i)
{
	int	a;
	bool bool_temp;

	a = 0;
	bool_temp = false;
	if (pipe(info->exe->fd) == -1)
		fc_error_tmp(1, "pipe");
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
			info->exe->path = fc_path_mlt_pipes(info, i);
			if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
				fc_error_tmp(1, "dup2");
			if (close(info->exe->fd[0]) == -1)
				fc_error_tmp(1, "close");
			if (close(info->exe->fd[1]) == -1)
				fc_error_tmp(1, "close");
			fc_execve_re(info, i, "stdout");
		}
	}
	else
	{
		if (wait(NULL) < 0)
			fc_error_tmp(1, "wait");
		if (close(info->exe->fd[1]) == -1)
			fc_error_tmp(1, "close");
		if (close(info->exe->tmp_fd) == -1)
			fc_error_tmp(1, "close");
		info->exe->tmp_fd = info->exe->fd[0];
	}
	return (0);
}
