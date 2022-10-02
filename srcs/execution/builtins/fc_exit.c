/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:34 by angelo            #+#    #+#             */
/*   Updated: 2022/10/02 12:50:54 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit(t_info *info)
{
	//if (strncmp(info->exe->cmds[info->idx2][info->idx], "exit", 5) == 0)
	if (strncmp(*info->exe->cmds[0], "exit", 5) == 0)
		exit (127);
	return (1);
}
