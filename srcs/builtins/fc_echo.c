/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:39:20 by angelo            #+#    #+#             */
/*   Updated: 2022/09/06 12:07:11 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_echo(t_info *info)
{
	int	i;
	int	size;
	int	option;

	i = 1;
	size = fc_argc_wt_exe(info);
	option = 0;
	if (strncmp(info->seg_command_line[1], "-n", 3) == 0)
		option = 1;
	if (option == 1)
		i = 2;
	while (info->seg_command_line[i])
	{
		if (size > i)
			printf("%s ", info->seg_command_line[i++]);
		else if (size == i)
			printf("%s", info->seg_command_line[i++]);
	}
	if (option == 0)
		printf("\n");
	return (0);
}
