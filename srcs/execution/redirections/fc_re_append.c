/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/01 18:45:37 by angelo            #+#    #+#             */
/*   Updated: 2022/10/02 20:47:52 by angelo           ###   ########.fr       */
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
		info->idx2 = 0;
		fc_builtins_or_execve(info);
	}
	
	info->exe->buffer = malloc(sizeof(char) * 1000);
	if (read(info->exe->fd[0], info->exe->buffer, 999) < 0)
		fc_error_tmp(1, "Problem with read\n");

	info->idx = 1;
	info->idx2 = 0;
	while (fc_path_for_execve(info) == NULL)
		info->idx++;
	
	info->exe->fd[0] = open(info->exe->cmds[info->idx2][info->idx], O_CREAT | O_RDWR, 0777);
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

	int	i = 0;
	int j = 0;
	int	end_line = 0;
//	int	size;
	char *str = get_next_line(info->exe->fd[0]);
	//while (get_next_line(info->exe->fd[0]))
	while (str[i])
	{
		j = 0;
		while (str[j] != '\0')
		{
			if (str[j] == '\n')
				end_line++;
			j++;
		}
		if (i == end_line)
			break ;
		i++;
		//printf("i = %d | end_line = %d\n", i, end_line);
	}
	printf("FIN : i = %d\n", i);
*/



/*
int	fc_re_append(t_info *info)
{
	if (pipe(info->exe->fd) < 0)
		fc_error_tmp(1, "Problem with pipe\n");
	info->exe->pid_init = fork();
	if (info->exe->pid_init < 0)
		fc_error_tmp(1, "Problem with fork\n");
	if (info->exe->pid_init == 0)
	{
		//info->exe->str_left = fc_create_left_str(info);
		fc_stdin_to_stdout(info);
		info->idx = 0;
		info->path = NULL;
		while (fc_path_for_execve(info) == NULL)
			info->idx++;
		info->path = fc_path_for_execve(info);
		//execve(info->path, info->exe->str_left, NULL);
	}
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

	int	i = 0;
	int j = 0;
	int	end_line = 0;
//	int	size;
	char *str = get_next_line(info->exe->fd[0]);
	//while (get_next_line(info->exe->fd[0]))
	while (str[i])
	{
		j = 0;
		while (str[j] != '\0')
		{
			if (str[j] == '\n')
				end_line++;
			j++;
		}
		if (i == end_line)
			break ;
		i++;
		//printf("i = %d | end_line = %d\n", i, end_line);
	}
	printf("FIN : i = %d\n", i);


	info->exe->buffer = malloc(sizeof(char) * 1000);
	if (read(info->exe->fd[0], info->exe->buffer, 999) < 0)
		fc_error_tmp(1, "Problem with read\n");

	//info->exe->str_right = fc_create_right_str(info);
	
	//info->exe->fd[0] = open(info->exe->str_right[0], O_CREAT | O_RDWR, 0777);
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

