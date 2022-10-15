/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:34 by angelo            #+#    #+#             */
/*   Updated: 2022/10/15 16:05:29 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit_m(t_info *info)
{
	if (ft_strncmp(*info->exe->cmds[0], "exit", 5) == 0)
	{
		write(1, "exit\n", 5);
		fc_final_free(info);
		exit (127);
	}
	return (1);
}

int	fc_exit(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
	{
		info->b->local_fd = STDOUT_FILENO;
		exit(127);
	}
	else
	{
		info->b->local_fd = STDOUT_FILENO;
		exit (127);
	}
	return (1);
}
