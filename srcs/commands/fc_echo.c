/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:39:20 by angelo            #+#    #+#             */
/*   Updated: 2022/09/05 23:31:11 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fc_argc_wt_exe(t_info *info)
{
	int	i;

	i = 0;
	while (info->seg_command_line[i])
		i++;
	return (i);
}

int	fc_echo(t_info *info)
{
	int	i;
	int	size;
	int	option;

	i = 1;
	size = fc_argc_wt_exe(info) - 1;
	printf("size = %d | i = %d\n", size, i);
	option = 0;
	while (info->seg_command_line[i])
	{
		if (strncmp(info->seg_command_line[1], "-n", 3) == 0)
		{
			option = 1;
			i++;
		}
		if (size > i)
			printf("%s ", info->seg_command_line[i++]);
		else if (size == i)
			printf("%s", info->seg_command_line[i++]);
	}
	if (option == 0)
		printf("\n");
	return (0);
}

//printf("option = %d\n", option);
//printf("\ni = %d | size = %d | option = %d\n", i, size, option);
//printf("NTM : %s\n", info->seg_command_line[5]);
