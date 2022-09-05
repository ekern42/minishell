/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 12:41:00 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 22:30:19 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_variable_command(t_info *info)
{
	(void)info;
	ft_putstr_fd("it's a variable\n", 1);
}

int	fc_check_variable(t_info *info)
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
				return (1);
		}
		b = -1;
	}
	return (0);
}
