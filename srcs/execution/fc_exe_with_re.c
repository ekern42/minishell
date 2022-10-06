/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_re.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:44:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/06 15:45:55 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_putstr_fd_re(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

int	fc_execute(char **arg, char *path, int tmp_fd, char **env)
{
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(path, arg, env);
	return (fc_putstr_fd_re("error: ", path));
}


int	fc_exe_with_re(t_info *info)
{
	int		i;
	int		tmp_fd;
	char	*path;

	i = 0;
	tmp_fd = dup(STDIN_FILENO);

	while (i < info->lex->nbr_pipe + 1) //check if the end is reached
	{
		if (i == info->lex->nbr_pipe) //exec in stdout
		{
			if (fork() == 0)
			{
				path = fc_path_mlt_pipes(info, i);
				if (fc_execute(info->exe->cmds[i], path, tmp_fd, (char**)info->envp))
					return (1);
			}
			else
			{
				close(tmp_fd);
				while(waitpid(-1, NULL, WUNTRACED) != -1)
					;
				tmp_fd = dup(STDIN_FILENO);
			}
		}
		else // envoie l'output dans un pipe
		{
			pipe(info->exe->fd);
			if (fork() == 0)
			{
				path = fc_path_mlt_pipes(info, i);
				dup2(info->exe->fd[1], STDOUT_FILENO);
				close(info->exe->fd[0]);
				close(info->exe->fd[1]);
				if (fc_execute(info->exe->cmds[i], path, tmp_fd, (char**)info->envp))
					return (1);
			}
			else
			{
				close(info->exe->fd[1]);
				close(tmp_fd);
				tmp_fd = info->exe->fd[0];
			}
		}
		i++;
	}
	close(tmp_fd);
	return (0);
}


/*
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
	while (j < info->lex->nbr_pipe)
	{
		info->exe->w_pid = waitpid(info->exe->pid_lst[i], WIFEXITED(true), 0);
		if (info->exe->w_pid < 0)
			fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
		if (info->exe->w_pid  > -1)
			printf("SUCCESS, i = %d\n", i);
		//i++;
		printf("i = %d | j = %d\n", i, j);
		if (i == j + i)
			break ;
		j++;
	}

	//info->exe->w_pid = waitpid(info->exe->pid_lst[3], WIFEXITED(true), 0);
	//if (info->exe->w_pid < 0)
	//	fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	//if (info->exe->w_pid  > -1)
	//	printf("SUCCESS, i = %d\n", i);
	

	//info->exe->w_pid = waitpid(info->exe->pid_lst[i], WIFEXITED(true), 0);
	//if (info->exe->w_pid < 0)
	//	fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	//if (info->exe->w_pid  > -1)
	//	printf("SUCCESS, i = %d\n", i);


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
