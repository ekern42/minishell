/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:34 by angelo            #+#    #+#             */
/*   Updated: 2022/09/11 18:07:36 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit(t_info *info)
{
	if (strncmp(info->seg_command_line[0], "exit", 5) == 0)
	{
		fc_free_seg_command_line(info);
		exit (127);
	}
	return (1);
}
