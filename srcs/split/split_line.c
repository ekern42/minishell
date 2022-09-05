/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:25:51 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 22:35:24 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_split_line(t_info *info)
{
	info->seg_command_line = ft_split(info->command_line, ' ');
	if (!info->seg_command_line)
		fc_error(info, 2);
}
