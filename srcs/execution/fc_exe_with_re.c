/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_re.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:44:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/05 19:00:26 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_putstr_fd2(char *str, char *arg)
{
	while (*str)
		write(2, str++, 1);
	if (arg)
		while(*arg)
			write(2, arg++, 1);
	write(2, "\n", 1);
	return (1);
}

int	ft_execute(char **arg, char *path, int tmp_fd, char **env)
{
	dup2(tmp_fd, STDIN_FILENO);
	close(tmp_fd);
	execve(path, arg, env);
	return (ft_putstr_fd2("error: ", path));
}


int	fc_exe_with_re(t_info *info)
{
	int		i;
	int		j;
	int		tmp_fd;
	char	*path = malloc(sizeof(char) * 100000);

	i = 0;
	j = 0;
	tmp_fd = dup(STDIN_FILENO);

	
	while (j < info->lex->nbr_pipe + 1) //check if the end is reached
	{
		if (j == info->lex->nbr_pipe) //exec in stdout
		{
			if ( fork() == 0)
			{
				path = "/usr/bin/wc";
				//fc_path_mlt_pipes(info, j);
				
				if (ft_execute(info->exe->cmds[j], path, tmp_fd, (char**)info->envp))
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
			if ( fork() == 0)
			{
				path = "/bin/ls";
				dup2(info->exe->fd[1], STDOUT_FILENO);
				close(info->exe->fd[0]);
				close(info->exe->fd[1]);
				if (ft_execute(info->exe->cmds[j], path, tmp_fd, (char**)info->envp))
					return (1);
			}
			else
			{
				close(info->exe->fd[1]);
				close(tmp_fd);
				tmp_fd = info->exe->fd[0];
			}
		}
		j++;
	}
	close(tmp_fd);
	return (0);
}

/*
static int	fc_init_exe_with_re(t_info *info)
{
	info->exe->pid_lst = NULL;
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
	int	fd_re[2];
	
	if (pipe(fd_re) < 0)
		fc_error_tmp(1, "Problem with pipe - fd_re\n");

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
				fc_stdout_and_stdin(info, fd_re);
			fc_builtins_or_execve(info);
		}
		i++;
	}

	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	//if (close(fd_re[0]) < 0)
	//	fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	//if (close(fd_re[1]) < 0)
	//	fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	info->exe->w_pid = waitpid(info->exe->pid_lst[1], WIFEXITED(true), 0);
	if (info->exe->w_pid < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	if (info->exe->w_pid  > -1)
		printf("SUCCESS, i = %d\n", i);
	

	info->exe->w_pid = waitpid(info->exe->pid_lst[2], WIFEXITED(true), 0);
	if (info->exe->w_pid < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	if (info->exe->w_pid  > -1)
		printf("SUCCESS, i = %d\n", i);


	info->exe->w_pid = waitpid(info->exe->pid_lst[3], WIFEXITED(true), 0);
	if (info->exe->w_pid < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	if (info->exe->w_pid  > -1)
		printf("SUCCESS, i = %d\n", i);

	return (0);
}
*/

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


/*
int	fc_exe_with_re(t_info *info)
{
	int	i;
	//int j;

	i = 1;
	while (i < info->lex->nbr_pipe + 2)
	{
		if (pipe(info->exe->fd_re[i]) < 0)
			fc_error_tmp(1, "Problem with pipe\n");
		//printf("i = %d\n", i);
		i++;
	}
	info->exe->pid_lst = NULL;
	info->exe->pid_lst = malloc(sizeof(pid_t) * (info->lex->nbr_pipe + 1));
	if (info->exe->pid_lst == NULL)
		fc_error_tmp(1, "Problem malloc\n");
	
	i = 0;
	while (i < info->lex->nbr_pipe + 1)
	{
		info->exe->pid_lst[i] = fork();
		if (info->exe->pid_lst[i] < 0)
			fc_error_tmp(1, "Problem with fork - info->exe->pid_lst[i]\n");
		while (info->exe->pid_lst[i] == 0)
		{
			if (i == 0)
			{
				if (close(info->exe->fd_re[1][0]) < 0)
					fc_error_tmp(1, "Problem with close - info->exe->fd_re[1][0]\n");
				if (close(info->exe->fd_re[1][1]) < 0)
					fc_error_tmp(1, "Problem with close - info->exe->fd_re[1][1]\n");
			}
			if (i == 1)
			{
				if (close(info->exe->fd_re[0][0]) < 0)
					fc_error_tmp(1, "Problem with close - info->exe->fd_re[0][0]\n");
				//if (close(info->exe->fd_re[0][1]) < 0)
				//	fc_error_tmp(1, "Problem with close - info->exe->fd_re[0][1]\n");
			}

			info->idx = 0;
			info->idx_re = i;
			if (i == 0)
				fc_stdin_to_stdout_re(info, i);
			else if (i == info->lex->nbr_pipe)
				fc_stdout_to_stdin_re(info, i);

			info->exe->path = NULL;
			info->exe->path = fc_path_mlt_pipes(info, info->idx_re);
			//info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx_re][info->idx];
			//info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx_re][info->idx];
			info->exe->cmds_execve = fc_create_tmp_str(info);
			if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
				fc_error_tmp(1, "Problem with fc_execve\n");
		}
		i++;
	}
	printf("NTM i = %d\n", i);
	//j = 0;
	//while (j < info->lex->nbr_pipe + 1)
	//{
	//	if (close(info->exe->fd_re[j][0]) < 0)
	//		fc_error_tmp(1, "Problem with close(info->exe->fd_re[j][0]\n");
	//	if (close(info->exe->fd_re[j][1]) < 0)
	//		fc_error_tmp(1, "Problem with close(info->exe->fd_re[j][1]\n");
	//	j++;
	//}
	//if (close(info->exe->fd_re[0][0]) < 0)
	//	fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	//if (close(info->exe->fd_re[0][1]) < 0)
	//	fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");
	//if (close(info->exe->fd_re[1][0]) < 0)
	//	fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	//if (close(info->exe->fd_re[1][1]) < 0)
	//	fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");
	//printf ("ntm i = %d\n", i);
	if (i == 2)
	{
		printf("first close\n");
		if (close(info->exe->fd_re[0][0]) < 0)
			fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
		//if (close(info->exe->fd_re[0][1]) < 0)
		//	fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");
	}

	if (i == 3)
	{
		printf("second close\n");
		if (close(info->exe->fd_re[1][0]) < 0)
			fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
		if (close(info->exe->fd_re[1][1]) < 0)
			fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");
	}

	info->exe->w_pid = waitpid(info->exe->pid_lst[0], WIFEXITED(true), 0);
	if (info->exe->w_pid < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	if (info->exe->w_pid  > -1)
		printf("1. SUCCESS, i = %d\n", i);

	info->exe->w_pid = waitpid(info->exe->pid_lst[1], WIFEXITED(true), 0);
	if (info->exe->w_pid < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	if (info->exe->w_pid  > -1)
		printf("2. SUCCESS, i = %d\n", i);


	

	//info->exe->w_pid = waitpid(info->exe->pid_lst[i], WIFEXITED(true), 0);
	//if (info->exe->w_pid < 0)
	//	fc_error_tmp(1, "Problem with waitpid - info->exe->w_pid\n");
	//if (info->exe->w_pid  > -1)
	//	printf("SUCCESS, i = %d\n", i);


	return (0);
}
*/