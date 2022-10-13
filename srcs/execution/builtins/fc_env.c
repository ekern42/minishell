/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:51:42 by angelo            #+#    #+#             */
/*   Updated: 2022/10/13 18:21:21 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_env(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
	{
		info->b->local_fd = info->exe->fd[1];
		fc_print_chainlist(info->envp, 's', info->b->local_fd);	
	}
	else
	{
		info->b->local_fd = 1; // last command = stdout
		fc_print_chainlist(info->envp, 's', info->b->local_fd);
	}
	exit (0);
}
