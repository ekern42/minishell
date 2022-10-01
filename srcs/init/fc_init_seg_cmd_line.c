/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_init_seg_cmd_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:02:43 by angelo            #+#    #+#             */
/*   Updated: 2022/10/01 10:01:47 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_init_seg_cmd_line(t_info *info)
{
	int a;
	
	info->exe = malloc(sizeof(t_execution));
	info->seg_command_line = ft_split(info->command_line, ' ');
//	fc_perfect_split(info);
	if (!info->seg_command_line)
		fc_error(info, 2);
	a = 0;
	while (info->seg_command_line[a])
		a++;
	info->exe->size_seg_cmd_line = a;
}

void	fc_init_seg_cmd_line2(t_info *info)
{
	info->exe = malloc(sizeof(t_execution));
	info->p = malloc(sizeof(t_path));
	info->b = malloc(sizeof(t_builtin));
	info->seg_command_line = ft_split(info->command_line, ' ');
	if (!info->seg_command_line)
		fc_error(info, 2);
}
