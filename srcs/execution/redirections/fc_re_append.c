/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:45:37 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 16:17:04 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	fc_init_re_append(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(1, "Problem with fork\n");
	return (0);
}

static int	fc_create_file(t_info *info)
{
	fc_find_idx_file(info, ">>", 3);
	info->exe->file = open(info->exe->cmds[info->idx_re][info->idx], O_CREAT | O_APPEND, 0777);
	if (info->exe->file < 0)
		fc_error_tmp(1, "Problem with open\n");
	if (close(info->exe->file) < 0)
		fc_error_tmp(1, "Problem with close(info->exe->file)\n");
	return (0);
}

int	fc_go_end_of_file(t_info *info)
{
	char	*str;
	int		fd;
	int		i;

	str = NULL;
	fd = open(info->exe->cmds[info->idx_re][info->idx], O_RDONLY);
	if (fd == -1)
		fc_error_tmp(1, "open() failed\n");


	i = 0;
	str = get_next_line(fd);
	while (str != NULL)
	{
		//printf("%s", str);
		str = get_next_line(fd);
		i++;
	}
	//printf("i = %d\n", i); // i = nombre de lignes
	if (close(fd) == -1)
		fc_error_tmp(1, "close() failed\n");

	return (0);
}

int	fc_re_append(t_info *info)
{
	fc_init_re_append(info);
	if (info->exe->pid_init == 0)
	{
		fc_stdin_to_stdout(info);
		info->idx = 0;
		fc_builtins_or_execve(info);
	}
	fc_create_file(info);
	
	info->exe->buffer = malloc(sizeof(char) * 1000);
	if (read(info->exe->fd[0], info->exe->buffer, 999) < 0)
		fc_error_tmp(1, "Problem with read\n");

	//fc_go_end_of_file(info);

	//printf("info->exe->buffer = %s\n", info->exe->buffer);

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
		fc_find_idx_file(info, ">>", 3);
		
		new_fd = open(info->exe->cmds[info->idx_re][info->idx], O_CREAT | O_RDWR | O_APPEND, 0777);
		if (new_fd < 0)
			fc_error_tmp(1, "Problem with open\n");
		
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