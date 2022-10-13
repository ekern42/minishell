/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:39:20 by angelo            #+#    #+#             */
/*   Updated: 2022/10/13 14:10:52 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	fc_check_is_option(t_info *info, int i)
{
	if (ft_strncmp(info->exe->cmds[i][1], "-n", 3) == 0)
	{
		info->b->j = 2;
		info->b->option = 1;
	}
	else
	{
		info->b->j = 1;
		info->b->option = 0;
	}
}

int	fc_echo(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe) //si not in last command
		info->b->local_fd = info->exe->fd[1]; // je sais pas pq ça marche avec fd[1] et pas fd[0]
	else
		info->b->local_fd = 1; // last command = stdout
	fc_check_is_option(info, i);
	while (info->exe->cmds[i][info->b->j])
	{
		ft_putstr_fd(info->exe->cmds[i][info->b->j], info->b->local_fd);
		if (info->exe->cmds[i][info->b->j + 1])
			ft_putstr_fd(" ", info->b->local_fd);
		info->b->j++;
	}
	if (!info->b->option)
		ft_putstr_fd("\n", info->b->local_fd);
	exit (0);
}
