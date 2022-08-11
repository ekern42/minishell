/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:25:51 by ekern             #+#    #+#             */
/*   Updated: 2022/08/11 11:12:16 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fc_split_line(t_info *info)
{
	info->seg_command_line = ft_split(info->command_line, ' ');
	if (!info->seg_command_line)
		fc_error(info ,2);
	
}