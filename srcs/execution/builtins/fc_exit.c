/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:34 by angelo            #+#    #+#             */
/*   Updated: 2022/10/14 11:13:50 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
	{
		//printf("1. not last\n");
		info->b->local_fd = info->exe->fd[1];
		//if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
		fc_final_free(info);
		exit(127);
	}
	else
	{
		//printf("2. last\n");
		info->b->local_fd = 1; // last command = stdout
		//if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
		fc_final_free(info);
		exit (127);
	}
	//return (1);
	exit (1);
}

/*
int	fc_exit(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
	{
		printf("1. not last\n");
		info->b->local_fd = info->exe->fd[1];
		//if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
		fc_final_free(info);
		exit(127);
	}
	else
	{
		printf("2. last\n");
		info->b->local_fd = 1; // last command = stdout
		//if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
		fc_final_free(info);
		exit (127);
	}
	//return (1);
	exit (1);
}
*/
/*
int	fc_exit(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
	{
		printf("1. not last\n");
		info->b->local_fd = info->exe->fd[1];
		//if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
		fc_final_free(info);
		exit(127);
	}
	else
	{
		printf("2. last\n");
		info->b->local_fd = 1; // last command = stdout
		//if (ft_strncmp(*info->exe->cmds[i], "exit", 5) == 0)
		fc_final_free(info);
		exit (127);
	}
	//return (1);
	exit (1);
}
*/
/*
int	fc_exit(t_info *info)
{
	if (strncmp(*info->exe->cmds[0], "exit", 5) == 0)
	{
		fc_final_free(info);
		exit (127);
	}
	return (1);
}
*/