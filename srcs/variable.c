/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 12:41:00 by ekern             #+#    #+#             */
/*   Updated: 2022/08/16 14:29:27 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void fc_check_variable_command(t_info *info)
{
	int	a;
	int	b;
	a = -1;
	b = -1;
//	printf("[]%s[]\n", info->seg_command_line[0]);
	while (info->seg_command_line[++a] != NULL)
	{
		while (info->seg_command_line[a][++b] != '\0')
		{
			if (info->seg_command_line[a][b] == '=')
			{
				
				break ;
			}
		}
		b = -1;
	}
}
