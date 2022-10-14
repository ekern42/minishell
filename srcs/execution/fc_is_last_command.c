/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_is_last_command.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 14:34:39 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 19:11:59 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_is_last_command(t_info *info, int i)
{
	int	a;

	a = 0;
	//info->pid = fork();
	//if (info->pid == 0)
	//{	
		/*while (info->exe->cmds[i][a] != NULL)
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
		}*/
		if (info->lex->error == false)
		{
			info->exe->path = fc_path_for_execve(info, i);
			//fc_execve(info, i, "stdout");
			//fc_builtins_or_execve(info, i, "stdout");
		}
	//}
	else
	{
		close(info->exe->fd[0]);
		// close(info->exe->fd[1]);
		waitpid(0, NULL, WCONTINUED);
		close(info->exe->fd[1]);
		// while (waitpid(-1, NULL, WUNTRACED) != -1);
		//if (close(info->exe->tmp_fd) == -1)
		//	fc_error_exe(1, "close");
		//info->exe->tmp_fd = dup(STDIN_FILENO);
		//if (info->exe->tmp_fd == -1)
		//	fc_error_exe(1, "dup");
	}
	return (0);
}
