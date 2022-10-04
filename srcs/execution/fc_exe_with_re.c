/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_re.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:44:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/04 17:47:57 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fc_init_exe_with_re(t_info *info)
{
	info->exe->pid_lst = malloc(sizeof(pid_t) * (info->lex->nbr_pipe + 1));
	if (info->exe->pid_lst == NULL)
		fc_error_tmp(1, "Problem malloc\n");
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe - info->exe->fd\n");
	return (0);
}

int	fc_exe_with_re(t_info *info)
{
	int	i;
	int	j;

	fc_init_exe_with_re(info);
	i = 0;
	while (i < info->lex->nbr_pipe + 1)
	{
		info->exe->pid_lst[i] = fork();
		if (info->exe->pid_lst[i] < 0)
			fc_error_tmp(1, "Problem with fork - info->exe->pid_lst[i]\n");
		//printf("i = %d\n", i);
		
		while (info->exe->pid_lst[i] == 0)
		{
			info->idx = 0;
			info->idx_re = i;
			if (i == 0)
				fc_stdin_to_stdout(info);
			else if (i == info->lex->nbr_pipe)
				fc_stdout_to_stdin(info);
			else
				fc_stdout_and_stdin(info);
			fc_builtins_or_execve(info);
		}
		i++;
	}

	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	j = 0;
	while (j < info->lex->nbr_pipe + 1)
	{
		info->exe->w_pid = waitpid(info->exe->pid_lst[i], WIFEXITED(true), 0);
		if (info->exe->w_pid < 0)
			fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
		j++;
	}

	return (0);
}


/*

	char *str_temp = malloc(sizeof(char) * 5);
	str_temp[0] = info->exe->cmds[0][0];
	str_temp[1] = info->exe->cmds[0][1];
	str_temp[2] = NULL;
	
	while (i < info->lex->nbr_pipe + 1)
	{
		//execute chaque commande
		info->exe->pid_lst[i] = fork();
		if (i == 0)
			fc_stdin_to_stdout(info);
		else if (i == info->lex->nbr_pipe) //derniere commande
			fc_stdout_to_stdin(info);
		else
			fc_stdout_and_stdin(info);
		printf("test\n");
		char path = (char)fc_path_for_execve2(info, i);
		printf("%d: %s %s\n", i, info->exe->cmds[i][0], info->exe->cmds[i][1]);
		execve(path, info->exe->cmds[i], (char **)info->envp);
		i++;
	}
}
*/



/*
int	fc_exe_with_re(t_info *info)
{
	int	i;
	int	j;

	fc_init_exe_with_re(info);
	i = 0;
	while (i < info->lex->nbr_pipe + 1)
	{
		info->exe->pid_lst[i] = fork();
		if (info->exe->pid_lst[i] < 0)
			fc_error_tmp(1, "Problem with fork - info->exe->pid_lst[i]\n");
		//printf("i = %d\n", i);
		
		while (info->exe->pid_lst[i] == 0)
		{
			if (i == 0)
			{
				fc_stdin_to_stdout(info);
				info->idx = 0;
				info->idx_re = 0;
				fc_builtins_or_execve(info);
			}
			else if (i == info->lex->nbr_pipe)
			{
				fc_stdout_to_stdin(info);
				info->idx = 0;
				info->idx_re = 1;
				fc_builtins_or_execve(info);
			}
			else
			{
				fc_stdout_and_stdin(info);
				info->idx = 0;
				info->idx_re = 2;
				fc_builtins_or_execve(info);
			}
		}
		i++;
	}

	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	j = 0;
	while (j < info->lex->nbr_pipe + 1)
	{
		info->exe->w_pid = waitpid(info->exe->pid_lst[i], WIFEXITED(true), 0);
		if (info->exe->w_pid < 0)
			fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
		j++;
	}

	return (0);
}
*/


/*
// GOOD VERSION WITH ONE PIPE WITHOUT DYNAMIC THING
int	fc_exe_with_re(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(6, "Problem with pipe(info->exe->fd)\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_init\n");

	if (info->exe->pid_init == 0)
	{
		fc_stdin_to_stdout(info);
		info->idx = 0;
		fc_builtins_or_execve(info);
	}
	info->exe->pid_other = fork();
	if (info->exe->pid_other < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_other\n");
	if (info->exe->pid_other == 0)
	{
		fc_stdout_to_stdin(info);
		info->idx = 0;
		info->idx_re = 1;
		fc_builtins_or_execve(info);
	}
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[1])\n");

	if (waitpid(info->exe->pid_init, WIFEXITED(1), 0) < 0)
		fc_error_tmp(5, "Problem with waitpid - info->exe->pid_init\n");
	if (waitpid(info->exe->pid_other, WIFEXITED(1), 0) < 0)
		fc_error_tmp(5, "Problem with waitpid - info->exe->pid_other\n");

	//if (waitpid(info->exe->pid_init, NULL, 0) < 0)
	//	fc_error_tmp(5, "Problem with waitpid - info->exe->pid_init\n");
	//if (waitpid(info->exe->pid_other, NULL, 0) < 0)
	//	fc_error_tmp(5, "Problem with waitpid - info->exe->pid_other\n");

	return (0);
}
*/


	//// ls -la
	//printf("%s\n", info->exe->cmds[0][0]);
	//printf("%s\n", info->exe->cmds[0][1]);
	//// wc -l
	//printf("%s\n", info->exe->cmds[1][0]);
	//printf("%s\n", info->exe->cmds[1][1]);
	//// ls -la
	//printf("%s\n", info->exe->cmds[2][0]);
	//printf("%s\n", info->exe->cmds[2][1]);