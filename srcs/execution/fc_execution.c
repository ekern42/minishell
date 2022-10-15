/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/10/15 12:49:01 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_is_re(t_info *info, int i, int fd)
{
	int	j;

	j = 0;
	info->exe->fd_re = fd;
	while (info->exe->cmds[i][j])
	{	
		if (ft_strncmp(info->exe->cmds[i][j], ">>", 3) == 0)
		{
			fc_re_append(info, i, j, info->exe->fd_re);
			break ;
		}
		else if (ft_strncmp(info->exe->cmds[i][j], ">", 2) == 0)
		{
			fc_re_output(info, i, j, info->exe->fd_re);
			break ;
		}
		else if (ft_strncmp(info->exe->cmds[i][j], "<", 2) == 0)
		{
			fc_re_input(info, i, j, info->exe->fd_re);
			break ;
		}
		j++;
	}
	return (0);
}

int	fc_execution(t_info *info)
{
	int	i;

	i = -1;
	info->exe->is_re = 0; //check si il y'a une redirection pour prendre le bonne input dans la prochaine commande
	while (info->exe->cmds[++i] != NULL)
	{
		if (pipe(info->exe->fd) == -1)
			fc_error_exe(1, "pipe");
		info->exe->pid = fork();
		if (info->exe->pid == -1)
			fc_error_exe(1, "fork");
		else if (info->exe->pid == 0)
		{
			if (dup2(info->exe->tmp_fd, STDIN_FILENO) == -1)
				fc_error_exe(1, "dup2");
			if (info->exe->cmds[i + 1] != NULL) // not last command
			{
				if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
					fc_error_exe(1, "dup2");
			}
			fc_is_re(info, i, info->exe->fd_re);
			/*j = 0;
			while (info->exe->cmds[i][j]) // check l'emplacement de la redirection
			{
				if (ft_strncmp(info->exe->cmds[i][j], ">>", 3) == 0)
				{
					fc_re_append(info, i, j, info->exe->fd_re);
					break ;
				}
				else if (ft_strncmp(info->exe->cmds[i][j], ">", 2) == 0)
				{
					fc_re_output(info, i, j, info->exe->fd_re);
					break ;
				}
				else if (ft_strncmp(info->exe->cmds[i][j], "<", 2) == 0)
				{
					fc_re_input(info, i, j, info->exe->fd_re);
					break ;
				}
				j++;
			}*/
			if (close(info->exe->fd[0]) == -1)
				fc_error_exe(1, "close");
			fc_builtins_or_execve(info, i);
		}
		else
		{
			if (waitpid(info->exe->pid, NULL, 0) == -1)
				fc_error_exe(1, "waitpid");
			if (close(info->exe->fd[1]) == -1)
				fc_error_exe(1, "close");
			if (info->exe->is_re) // si il y'a une redirection il faut prendre le fd du fichier 
			{
				info->exe->tmp_fd = info->exe->fd_re;
				info->exe->is_re = 0;
			}
			else
				info->exe->tmp_fd = info->exe->fd[0];
		}
	}
	return (0);
}


/*
WITH REDIRECTION : >> INSIDE FUNCTION
int	fc_execution(t_info *info)
{
	int	i;
	int	j;
	int	fd;
	int	is_redirection; //check si il y'a une redirection pour prendre le bonne input dans la prochaine commande

	i = -1;
	is_redirection = 0;
	while (info->exe->cmds[++i] != NULL)
	{
		if (pipe(info->exe->fd) == -1)
			fc_error_exe(1, "pipe");
		info->exe->pid = fork();
		if (info->exe->pid == -1)
			fc_error_exe(1, "fork");
		else if (info->exe->pid == 0)
		{
			if (dup2(info->exe->tmp_fd, STDIN_FILENO) == -1)
				fc_error_exe(1, "dup2");
			if (info->exe->cmds[i + 1] != NULL) // not last command
			{
				if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
					fc_error_exe(1, "dup2");
			}
			j = 0;
			while (info->exe->cmds[i][j]) // check l'emplacement de la redirection
			{
				if (ft_strncmp(info->exe->cmds[i][j], ">>", 3) == 0)
				{
					fd = open(info->exe->cmds[i][j + 1], O_WRONLY | O_CREAT | O_APPEND, 0644);
					if (fd == -1)
						fc_error_exe(1, "open");
					if (dup2(fd, STDOUT_FILENO) == -1)
						fc_error_exe(1, "dup2");
					if (close(fd) == -1)
						fc_error_exe(1, "close");
					info->exe->cmds[i][j] = NULL; // faire attention au leaks sur le reste de la chaine qu on pert potentiellement ici
					if (info->exe->cmds[i + 1] != NULL)
						info->exe->fd[1] = fd;
					fc_builtins_or_execve(info, i);
					is_redirection = 1; // indique qu'il y a une redirection
					break;
				}
				j++;
			}
			if (close(info->exe->fd[0]) == -1)
				fc_error_exe(1, "close");
			fc_builtins_or_execve(info, i);
		}
		else
		{
			if (waitpid(info->exe->pid, NULL, 0) == -1)
				fc_error_exe(1, "waitpid");
			if (close(info->exe->fd[1]) == -1)
				fc_error_exe(1, "close");
			if (is_redirection) // si il y'a une redirection il faut prendre le fd du fichier 
			{
				info->exe->tmp_fd = fd;
				is_redirection = 0;
			}
			else
				info->exe->tmp_fd = info->exe->fd[0];
		}
	}
	return (0);
}
*/


/*
// WITHOUT REDIRECTION
int	fc_execution(t_info *info)
{
	int	i;

	i = -1;
	while (info->exe->cmds[++i] != NULL)
	{
		if (pipe(info->exe->fd) == -1)
			fc_error_exe(1, "pipe");
		info->exe->pid = fork();
		if (info->exe->pid == -1)
			fc_error_exe(1, "fork");
		else if (info->exe->pid == 0)
		{
			if (dup2(info->exe->tmp_fd, STDIN_FILENO) == -1)
				fc_error_exe(1, "dup2");
			if (info->exe->cmds[i + 1] != NULL)
			{
				if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
					fc_error_exe(1, "dup2");
			}
			if (close(info->exe->fd[0]) == -1)
				fc_error_exe(1, "close");
			fc_builtins_or_execve(info, i);
		}
		else
		{
			if (waitpid(info->exe->pid, NULL, 0) == -1)
				fc_error_exe(1, "waitpid");
			if (close(info->exe->fd[1]) == -1)
				fc_error_exe(1, "close");
			info->exe->tmp_fd = info->exe->fd[0];
		}
	}
	return (0);
}
*/
