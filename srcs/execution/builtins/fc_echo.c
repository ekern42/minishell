/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:39:20 by angelo            #+#    #+#             */
/*   Updated: 2022/10/12 17:36:04 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
/*
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
	size = fc_argc_wt_exe(info);
	//size = info->split_size;
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
*/
int	fc_echo(t_info *info)
{
	(void)info;
	
	ft_putstr_fd("echo\nOk but change info->seg_command_line and check with redirection\n", 1);
	ft_putstr_fd("echo\nOk but change info->seg_command_line and check with redirection\n", 2);
	exit (0);
	//return (0);
}
