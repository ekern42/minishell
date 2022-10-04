/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_re.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:44:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/04 13:24:45 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_exe_with_re(t_info *info)
{
	int	i;
	
	info->exe->pid_lst = malloc(sizeof(pid_t) * (info->lex->nbr_pipe + 1));
	if (info->exe->pid_lst == NULL)
		fc_error_tmp(1, "Problem malloc\n");

	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe(info->exe->fd)\n");

	i = 0;
	while (i < info->lex->nbr_pipe + 1)
	{
		//printf("i = %d\n", i);
		info->exe->pid_lst[i] = fork();
		if (info->exe->pid_lst[i] < 0)
			fc_error_tmp(1, "Problem with info->exe->pid_lst[i]\n");
		if (i == 0 && info->exe->pid_lst[i] == 0)
		{
			fc_stdin_to_stdout(info);
			info->idx = 0;
			fc_builtins_or_execve(info);
		}
		else if (i == info->lex->nbr_pipe && info->exe->pid_lst[i] == 0)
		{
			fc_stdout_to_stdin(info);
			info->idx = 0;
			info->idx_re = 1;
			fc_builtins_or_execve(info);
		}
		i++;
	}

	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	info->exe->w_pid = info->lex->nbr_pipe;
	//printf("i = %d\n", i);
	while (info->exe->w_pid > 0)
	{
		//printf("i = %d\n", i);
		if (waitpid(info->exe->pid_lst[i], NULL, 0) < 0)
			fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
		info->exe->w_pid--;
	}

	return (0);
}

/*
int	fc_exe_with_pipe(t_info info)
{

	char *str_temp = malloc(sizeof(char) * 5);
	str_temp[0] = info->exe->cmds[0][0];
	str_temp[1] = info->exe->cmds[0][1];
	str_temp[2] = NULL;
	
	info->exe->pid_lst = malloc(sizeof(pid_t) (info->lex->nbr_pipe + 1));
	int i;
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(6, "Problem with pipe(info->exe->fd)\n");

	i = 0;

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


	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[1])\n");

	i = 0;
	while (i < info->lex->nbr_pipe + 1)
	{
		if (waitpid(info->exe->pid_lst[i], NULL, 0) < 0)
			fc_error_tmp(5, "Problem with waitpid - info->exe->pid_init\n");
		i++;
	}
	return (0);
}
*/

/*
// Good version for one pipe
int	fc_exe_with_pipe(t_info *info)
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
		info->idx2 = 1;
		fc_builtins_or_execve(info);
	}
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(6, "Problem with close(info->exe->fd[1])\n");

	if (waitpid(info->exe->pid_init, NULL, 0) < 0)
		fc_error_tmp(5, "Problem with waitpid - info->exe->pid_init\n");
	if (waitpid(info->exe->pid_other, NULL, 0) < 0)
		fc_error_tmp(5, "Problem with waitpid - info->exe->pid_other\n");

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