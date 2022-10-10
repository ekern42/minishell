/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exe_with_re.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/04 12:44:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/10 19:27:53 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_exe_with_re(t_info *info)
{
	int	i;

	i = 0;
	info->exe->tmp_fd = dup(STDIN_FILENO);
	if (info->exe->tmp_fd == -1)
		fc_error_tmp(1, "dup");
	while (i < info->lex->nbr_pipe + 1)
	{
		//printf("i = %d\n", i);
		if (i == info->lex->nbr_pipe)
			fc_is_last_command(info, i);
		else // envoie l'output dans un pipe
			fc_not_in_last_command(info, i);
		i++;
	}
	if (close(info->exe->tmp_fd) == -1)
		fc_error_tmp(1, "close");
	return (0);
}

int	fc_putstr_fd_re(char *str, t_info *info)
{
	while (*str)
		write(2, str++, 1);
	if (info->exe->path)
		while(*info->exe->path)
			write(2, info->exe->path++, 1);
	write(2, "\n", 1);
	return (1);
}


int	fc_is_last_command(t_info *info, int i)
{
	if (fork() == 0)
	{
		info->exe->path = fc_path_mlt_pipes(info, i);
		fc_execve_re(info, i);
		//fc_builtins_or_execve(info, i);
	}
	else
	{
		if (close(info->exe->tmp_fd) == -1)
			fc_error_tmp(1, "close");
		while(waitpid(-1, NULL, WUNTRACED) != -1)
			;
		info->exe->tmp_fd = dup(STDIN_FILENO);
		if (info->exe->tmp_fd == -1)
			fc_error_tmp(1, "dup");
	}
	return (0);
}

int	fc_not_in_last_command(t_info *info, int i)
{
	int	fd;
	char *strtemp;
	int	a;
	bool	bool_temp;

	a = 0;
	bool_temp = false;
	if (pipe(info->exe->fd) == -1)
	{
		fc_error_tmp(1, "pipe");
	}
	if (fork() == 0)
	{
		while (info->exe->cmds[i][a] != NULL && bool_temp == false)
		{
			strtemp = info->exe->cmds[i][a];
			if ((fc_re_append(info, a, i)) == 1)	
				bool_temp = true;
			a++;
		}
		if (bool_temp == true)
		{
			info->exe->path = fc_path_mlt_pipes(info, i);
			fc_execve_re(info, i);
			info->exe->cmds[i][a - 1] = strtemp;
		}
		else
		{	
			info->exe->path = fc_path_mlt_pipes(info, i);
			if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
				fc_error_tmp(1, "dup2");
			if (close(info->exe->fd[0]) == -1)
				fc_error_tmp(1, "close");
			if (close(info->exe->fd[1]) == -1)
				fc_error_tmp(1, "close");
			fc_execve_re(info, i);
		}
	}
	else
	{
			//printf("%s\n", info->exe->cmds[i][a]);
			if (info->lex->re_append == true)
			{
				if (wait(NULL) < 0)
					fc_error_tmp(1, "wait");
				while (ft_strncmp(info->exe->cmds[i][a],">>", 3) != 0)
					a++;
				fd = open(info->exe->cmds[i][a + 1], O_RDONLY);
				if (fd == -1)
					fc_error_tmp(1, "open");
			}
			if (close(info->exe->fd[1]) == -1)
				fc_error_tmp(1, "close");
			if (close(info->exe->tmp_fd) == -1)
				fc_error_tmp(1, "close");
			if (info->lex->re_append == true)
				info->exe->tmp_fd = fd;
			else
				info->exe->tmp_fd = info->exe->fd[0];
	}
	return (0);
}


/*
int	fc_not_in_last_command(t_info *info, int i)
{
	int	fd;

	if (pipe(info->exe->fd) == -1)
		fc_error_tmp(1, "pipe");
	if (fork() == 0)
	{
		if (strcmp(info->exe->cmds[i][2],">>") == 0)
		{
			//ft_putstr_fd("detect", 2);
			fd = open(info->exe->cmds[i][3], O_WRONLY | O_CREAT | O_APPEND , 0777);
			if (dup2(fd, STDOUT_FILENO) == -1)
				fc_error_tmp(1, "dup2");
			if (close(info->exe->fd[0]) == -1)
				fc_error_tmp(1, "close");
			close(fd);
			//if (close(fd) == -1)
			//	fc_error_tmp(1, "close");
			//(void)file;
			info->exe->cmds[i][2] = NULL;

		}
		// decommenter et enlever le if du dessus si on ne veut plus les redirections
		//if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
		//    fc_error_tmp(1, "dup2");
		//if (close(info->exe->fd[0]) == -1)
		//    fc_error_tmp(1, "close");
		//if (close(info->exe->fd[1]) == -1)
		//    fc_error_tmp(1, "close");
		info->exe->path = fc_path_mlt_pipes(info, i);
		fc_execve_re(info, i);
	}
	else
	{
		if (ft_strncmp(info->exe->cmds[i][2],">>", 3) == 0){
			usleep(10000); //a mon avis je devrais plutot mettre waitpid ici (si je met pas de sleep ou de wait le on as pas le temps de s'ouvrir / d'ecrire dedans dans le procesus enfant)
			fd = open(info->exe->cmds[i][3], O_RDONLY);
		}
		if (fd < 0)
			ft_putstr_fd("la", 2);
		if (close(info->exe->fd[1]) == -1)
			fc_error_tmp(1, "close");
		if (close(info->exe->tmp_fd) == -1)
			fc_error_tmp(1, "close");
		info->exe->tmp_fd = fd;
	}
	return (0);
}
*/
//ls -la >> test.txt | grep total
//ls -la >> test.txt | wc -l

/*
int	fc_not_in_last_command(t_info *info, int i)
{
	if (pipe(info->exe->fd) == -1)
		fc_error_tmp(1, "pipe");
	if (fork() == 0)
	{
		info->exe->path = fc_path_mlt_pipes(info, i);
		if (dup2(info->exe->fd[1], STDOUT_FILENO) == -1)
			fc_error_tmp(1, "dup2");
		if (close(info->exe->fd[0]) == -1)
			fc_error_tmp(1, "close");
		if (close(info->exe->fd[1]) == -1)
			fc_error_tmp(1, "close");
		fc_execve_re(info, i);
		//fc_builtins_or_execve(info, i);
	}
	else
	{
		if (close(info->exe->fd[1]) == -1)
			fc_error_tmp(1, "close");
		if (close(info->exe->tmp_fd) == -1)
			fc_error_tmp(1, "close");
		info->exe->tmp_fd = info->exe->fd[0];
	}
	return (0);
}
*/