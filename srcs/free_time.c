/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:45:01 by ekern             #+#    #+#             */
/*   Updated: 2022/08/11 11:20:01 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fc_free_seg_command_line(t_info *info)
{
	int	a;

	a = -1;
	while (info->seg_command_line[++a] != NULL)
		free(info->seg_command_line[a]);
}

void fc_final_free(t_info *info)
{
	fc_free_seg_command_line(info);
}