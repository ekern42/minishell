/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_pipe.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 11:06:00 by angelo            #+#    #+#             */
/*   Updated: 2022/10/02 17:31:35 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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


/*
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
		//execve(info->path, info->exe->cmds[info->idx2], NULL);
	}
	//info->idx2 = 1;
	info->exe->pid_other = fork();
	if (info->exe->pid_other < 0)
		fc_error_tmp(5, "Problem with info->exe->pid_other\n");
	if (info->exe->pid_other == 0)
	{
		fc_stdout_to_stdin(info);
		info->idx = 0; 
		//while (fc_path_for_execve(info) == NULL) // Pourquoi le while n'est plus nécessaire ???
		//	info->idx++;
		info->idx2 = 1;
		//info->path = fc_path_for_execve(info);
		fc_builtins_or_execve(info);
		//execve(info->path, info->exe->cmds[info->idx2], NULL);
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