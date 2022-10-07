/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:45:37 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 12:36:44 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//fc_create_left_str(info);
//fc_print_str_left(info);
//printf("%s\n", info->exe->cmds[0][0]);
//printf("%s\n", info->exe->cmds[0][1]);
//printf("%s\n", info->exe->cmds[0][2]);
//printf("%s\n", info->exe->cmds[0][3]);

//printf("%s\n", info->exe->cmds[1][0]); // segfault
//printf("%s\n", info->exe->cmds[1][1]); // segfault

static	int	fc_find_idx_file(t_info *info)
{
	info->idx = 0;
	while (info->exe->cmds[info->idx_re][info->idx++] != NULL)
	{
		if (strncmp(info->exe->cmds[info->idx_re][info->idx], ">>", 3) == 0)
		{
			info->idx++;
			break ;
		}
	}
	return (info->idx);
}

int	fc_re_append(t_info *info)
{
//	int	i;

	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(1, "Problem with fork\n");
	if (info->exe->pid_init == 0)
	{
		fc_stdin_to_stdout(info);
		info->idx = 0;
		fc_builtins_or_execve(info);
	}


	fc_find_idx_file(info);
	info->exe->file = open(info->exe->cmds[info->idx_re][info->idx], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (info->exe->file < 0)
		fc_error_tmp(1, "Problem with open\n");
	
	if (close(info->exe->file) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->file)\n");


	info->exe->buffer = malloc(sizeof(char) * 1000);
	if (read(info->exe->fd[0], info->exe->buffer, 999) < 0)
		fc_error_tmp(1, "Problem with read\n");


	info->exe->fd[0] = open(info->exe->cmds[info->idx_re][info->idx], O_WRONLY, 0777);
	if (info->exe->fd[0] < 0)
		fc_error_tmp(1, "Problem with open\n");

	if (write(info->exe->fd[0], info->exe->buffer, ft_strlen(info->exe->buffer)) < 0)
		fc_error_tmp(1, "Problem with write\n");


	if (close (info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	if (waitpid(info->exe->pid_init, NULL, 0) < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->pid_init\n");
	
	return (0);
}


/*
int	fc_re_append(t_info *info)
{
	int		new_fd;
	ssize_t	r;
	int		size;

	info->exe->buff = NULL;
	info->exe->buff = malloc(sizeof(char) * 1000);

	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(1, "Problem with fork\n");
	if (info->exe->pid_init == 0)
	{
		new_fd = open(info->exe->cmds[info->idx_re][3], O_CREAT | O_RDWR | O_APPEND, 0777);
		if (new_fd < 0)
			fc_error_tmp(1, "Problem with open\n");


		//fc_stdin_to_stdout(info);
		if (dup2(info->exe->fd[1], STDOUT_FILENO) < 0)
			fc_error_tmp(1, "Problem with dup2 - info->exe->fd[1], STDOUT_FILENO\n");
		if (close(info->exe->fd[0]) < 0)
			fc_error_tmp(1, "Problem with close - fd[0]- fc_stdin_to_stdout\n");
		if (close(info->exe->fd[1]) < 0)
			fc_error_tmp(1, "Problem with close - fd[1]- fc_stdin_to_stdout\n");
		info->idx = 0;
		info->exe->path = NULL;
		info->exe->path = fc_path_for_execve(info);
		info->exe->cmds_execve = fc_create_left_str(info);
		if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
			fc_error_tmp(1, "Problem with fc_execve_redir\n");
	}
	else
	{
		//new_fd = open(info->exe->cmds[info->idx_re][3], O_CREAT | O_RDWR | O_APPEND, 0777);
		//if (new_fd < 0)
		//	fc_error_tmp(1, "Problem with open\n");
		
		size = 10;
		r = read(info->exe->fd[0], info->exe->buff, size);
		if (r == -1)
			fc_error_tmp(1, "Problem with read\n");
		while (r)
		{
			//printf("Read %zd bytes\n", r);
			write(new_fd, info->exe->buff, r);
			//printf("Writing %zd\n", r);
			r = read(info->exe->fd[0], info->exe->buff, size);
		}

		
		if (close (new_fd) < 0)
			fc_error_tmp(1, "Problem with close(new_fd)\n");

		if (close (info->exe->fd[0]) < 0)
			fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
		if (close(info->exe->fd[1]) < 0)
			fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

		if (waitpid(info->exe->pid_init, WIFEXITED(true), 0) < 0)
			fc_error_tmp(1, "Problem with waitpid - info->exe->pid_init\n");
	
	}
	return (0);
}
*/

/*
// Avant de trouver la taille dynamiquement pour le malloc de buffer
int	fc_re_append(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(1, "Problem with fork\n");
	if (info->exe->pid_init == 0)
	{
		fc_stdin_to_stdout(info);
		info->idx = 0;
		fc_builtins_or_execve(info);
	}

	info->exe->buffer = malloc(sizeof(char) * 1000);
	if (read(info->exe->fd[0], info->exe->buffer, 999) < 0)
		fc_error_tmp(1, "Problem with read\n");

	info->idx = 1;
	while (fc_path_for_execve(info) == NULL)
		info->idx++;

	//info->exe->fd[0] = open(info->exe->cmds[info->idx_re][info->idx], O_CREAT | O_RDWR, 0777);
	info->exe->fd[0] = open(info->exe->cmds[info->idx_re][info->idx], O_CREAT | O_RDWR | O_APPEND, 0777);
	if (info->exe->fd[0] < 0)
		fc_error_tmp(1, "Problem with open\n");

	if (write(info->exe->fd[0], info->exe->buffer, ft_strlen(info->exe->buffer)) < 0)
		fc_error_tmp(1, "Problem with write\n");

	if (close (info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[0])\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->fd[1])\n");

	if (waitpid(info->exe->pid_init, NULL, 0) < 0)
		fc_error_tmp(1, "Problem with waitpid - info->exe->pid_init\n");
	
	return (0);
}
*/


// Prototype : char *get_next_line(int fd)
//printf("%s", get_next_line(info->exe->fd[0]));
//printf("%s", get_next_line(info->exe->fd[0]));
//printf("%s", get_next_line(info->exe->fd[0]));
//printf("%s", get_next_line(info->exe->fd[0]));
//printf("%s", get_next_line(info->exe->fd[0]));
//printf("%s", get_next_line(info->exe->fd[0]));
//printf("%s", get_next_line(info->exe->fd[0]));
//printf("%s", get_next_line(info->exe->fd[0]));

//printf("%s", get_next_line(info->exe->fd[0]));


// Hajar variant
//while ((r = read(info->exe->fd[0], info->exe->buff, 1024)) > 0)
//{
//	printf("1. salut\n");
//	//printf("Read %zd bytes\n", r);
//	write(new_fd, info->exe->buff, r);
//	//printf("Writing %zd\n", r);
//	//r = read(info->exe->fd[0], info->exe->buff, 1024);
//}
//printf("2. salut\n");