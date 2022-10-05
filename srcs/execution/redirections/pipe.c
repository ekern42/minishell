/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 19:36:10 by angelo            #+#    #+#             */
/*   Updated: 2022/10/05 16:05:35 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"


int	fc_stdin_to_stdout_re(t_info *info, int i)
{	
	printf("fc_stdin_to_stdout_re : i = %d\n", i);
	if (i == 0)
	{
		if (close(info->exe->fd_re[1][0]) < 0)
			fc_error_tmp(1, "Problem with close - info->exe->fd_re[1][0]- fc_stdin_to_stdout\n");
		if (close(info->exe->fd_re[1][1]) < 0)
			fc_error_tmp(1, "Problem with close - info->exe->fd_re[1][1]- fc_stdin_to_stdout\n");
	}
	if (i == 1)
	{
		if (close(info->exe->fd_re[0][0]) < 0)
			fc_error_tmp(1, "Problem with close - info->exe->fd_re[0][0]- fc_stdin_to_stdout\n");
		if (close(info->exe->fd_re[0][1]) < 0)
			fc_error_tmp(1, "Problem with close - info->exe->fd_re[0][1]- fc_stdin_to_stdout\n");
	}
	if (dup2(info->exe->fd_re[i][1], STDOUT_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - info->exe->fd_re[i][1], STDOUT_FILENO\n");
	if (close(info->exe->fd_re[i][0]) < 0)
		fc_error_tmp(1, "Problem with close - info->exe->fd_re[i][0]- fc_stdin_to_stdout\n");
	//if (close(info->exe->fd_re[i][1]) < 0)
	//	fc_error_tmp(1, "Problem with close - info->exe->fd_re[i][1]- fc_stdin_to_stdout\n");
	return (0);
}


int	fc_stdout_to_stdin_re(t_info *info, int i)
{
	printf("fc_stdout_to_stdin_re : i = %d\n", i);
	if (i == 0)
	{
		if (close(info->exe->fd_re[1][0]) < 0)
			fc_error_tmp(1, "Problem with close - info->exe->fd_re[1][0]- fc_stdout_to_stdin\n");
		if (close(info->exe->fd_re[1][1]) < 0)
			fc_error_tmp(1, "Problem with close - info->exe->fd_re[1][1]- fc_stdout_to_stdin\n");
	}
	if (i == 1)
	{
		if (close(info->exe->fd_re[0][0]) < 0)
			fc_error_tmp(1, "Problem with close - info->exe->fd_re[0][0]- fc_stdout_to_stdin\n");
		//if (close(info->exe->fd_re[0][1]) < 0)
		//	fc_error_tmp(1, "Problem with close - info->exe->fd_re[0][1]- fc_stdout_to_stdin\n");
	}
	if (dup2(info->exe->fd_re[i][0], STDIN_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - info->exe->fd_re[i][0], STDIN_FILENO\n");
	if (close(info->exe->fd_re[i][0]) < 0)
		fc_error_tmp(1, "Problem with close - info->exe->fd_re[i][0] - fc_stdout_to_stdin\n");
	if (close(info->exe->fd_re[i][1]) < 0)
		fc_error_tmp(1, "Problem with close - info->exe->fd_re[i][1]- fc_stdout_to_stdin\n");
	//if (close(info->exe->fd_re[0][1]) < 0)
	//		fc_error_tmp(1, "Problem with close - info->exe->fd_re[0][1]- NTM\n");
	return (0);
}

int	fc_stdout_and_stdin_re(t_info *info, int i)
{
	if (i == 0)
	{
		if (close(info->exe->fd_re[1][0]) < 0)
			fc_error_tmp(1, "Problem with close - fd_re[0]- fc_stdin_to_stdout\n");
		if (close(info->exe->fd_re[1][1]) < 0)
			fc_error_tmp(1, "Problem with close - fd_re[1]- fc_stdin_to_stdout\n");
	}
	if (i == 1)
	{
		if (close(info->exe->fd_re[0][0]) < 0)
			fc_error_tmp(1, "Problem with close - fd_re[0]- fc_stdin_to_stdout\n");
		if (close(info->exe->fd_re[0][1]) < 0)
			fc_error_tmp(1, "Problem with close - fd_re[1]- fc_stdin_to_stdout\n");
	}
	if (dup2(info->exe->fd_re[i][0], STDIN_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - NTM1 - info->exe->fd_re[0], STDIN_FILENO\n");
	if (close(info->exe->fd_re[i][0]) < 0)
		fc_error_tmp(1, "Problem with close - NTM1 - fd_re[0] - fc_stdout_and_stdin\n");
	
	if (dup2(info->exe->fd_re[i][1], STDOUT_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - NTM2 - info->exe->fd_re[1], STDOUT_FILENO\n");
	if (close(info->exe->fd_re[i][1]) < 0)
		fc_error_tmp(1, "Problem with close - NTM2 - fd_re[1]- fc_stdout_and_stdin\n");

	return (0);
}










// Donc à gauche du pipe
int	fc_stdin_to_stdout(t_info *info)
{
	if (dup2(info->exe->fd[1], STDOUT_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - info->exe->fd[1], STDOUT_FILENO\n");
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close - fd[0]- fc_stdin_to_stdout\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close - fd[1]- fc_stdin_to_stdout\n");
	return (0);
}

// Donc à droite du pipe
int	fc_stdout_to_stdin(t_info *info)
{
	if (dup2(info->exe->fd[0], STDIN_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - info->exe->fd[0], STDIN_FILENO\n");
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close - fd[0] - fc_stdout_to_stdin\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close - fd[1]- fc_stdout_to_stdin\n");
	return (0);
}

int	fc_stdout_and_stdin(t_info *info)
{
	if (dup2(info->exe->fd[0], STDIN_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - NTM1 - info->exe->fd[0], STDIN_FILENO\n");
	if (close(info->exe->fd[0]) < 0)
		fc_error_tmp(1, "Problem with close - NTM1 - fd[0] - fc_stdout_and_stdin\n");
	
	if (dup2(info->exe->fd[1], STDOUT_FILENO) < 0)
		fc_error_tmp(1, "Problem with dup2 - NTM2 - info->exe->fd[1], STDOUT_FILENO\n");
	if (close(info->exe->fd[1]) < 0)
		fc_error_tmp(1, "Problem with close - NTM2 - fd[1]- fc_stdout_and_stdin\n");

	return (0);
}
