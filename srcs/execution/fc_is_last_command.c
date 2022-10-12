/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_is_last_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:34:39 by angelo            #+#    #+#             */
/*   Updated: 2022/10/12 17:43:53 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
			//printf("ntm = %s\n", *info->exe->cmds[i]);
			info->exe->path = fc_path_for_execve(info, i);
			fc_builtins_or_execve(info, i, "stdout");
		}
	}
	else
	{
		while (waitpid(-1, NULL, WUNTRACED) != -1)
			;
		if (close(info->exe->tmp_fd) == -1)
			fc_error_exe(1, "close");
		info->exe->tmp_fd = dup(STDIN_FILENO);
		if (info->exe->tmp_fd == -1)
			fc_error_exe(1, "dup");
	}
	return (0);
}
