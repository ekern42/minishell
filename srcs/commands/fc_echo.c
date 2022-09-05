/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:39:20 by angelo            #+#    #+#             */
/*   Updated: 2022/09/05 17:09:36 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int fc_echo(t_info *info)
{
	int	i;
	int	j;

	i = 1;
	while (info->seg_command_line[i][j])
	{
		j = 0;
		while (info->seg_command_line[i][j] != '\0')
		{
			//printf("%c", info->seg_command_line[i][j]);
			
			printf("info->seg_command_line[i][j] = %c | i = %d | j = %d\n", info->seg_command_line[i][j], i, j);
			j++;
		}
		i++;		
	}
	printf("\n");
	return (0);
}


/*
int fc_echo(t_info *info)
{
	int	i;

	i = 1;
	while (info->seg_command_line[i])
	{
		printf("%s", info->seg_command_line[i]);
		i++;		
	}
	printf("\n");
	return (0);
}
*/