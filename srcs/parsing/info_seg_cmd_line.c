/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info_seg_cmd_line.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:41 by angelo            #+#    #+#             */
/*   Updated: 2022/10/01 14:18:16 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
/*
int	fc_info_seg_cmd_line(t_info *info)
{
	int	i;

	info->exe->nbr_pipe = 0;
	info->exe->nbr_bracket_smaller_one = 0;
	info->exe->nbr_bracket_smaller_two = 0;
	info->exe->nbr_bracket_bigger_one = 0;
	info->exe->nbr_bracket_bigger_two = 0;
	i = 0;
	while (info->seg_command_line[++i] != NULL)
	{
		if (strncmp(info->seg_command_line[i], "|", 2) == 0)
			info->exe->nbr_pipe++;
		else if (strncmp(info->seg_command_line[i], "<", 2) == 0)
			info->exe->nbr_bracket_smaller_one++;
		else if (strncmp(info->seg_command_line[i], "<<", 3) == 0)
			info->exe->nbr_bracket_smaller_two++;
		else if (strncmp(info->seg_command_line[i], ">", 2) == 0)
			info->exe->nbr_bracket_bigger_one++;
		else if (strncmp(info->seg_command_line[i], ">>", 3) == 0)
			info->exe->nbr_bracket_bigger_two++;
	}
	info->exe->size_seg_cmd_line = i;
	printf("nbr | : %d\n", info->exe->nbr_pipe);
	printf("nbr < : %d\n", info->exe->nbr_bracket_smaller_one);
	printf("nbr << : %d\n", info->exe->nbr_bracket_smaller_two);
	printf("nbr > : %d\n", info->exe->nbr_bracket_bigger_one);
	printf("nbr >> : %d\n", info->exe->nbr_bracket_bigger_two);
	printf("size_seg_cmd_line : %d\n", info->exe->size_seg_cmd_line);
	return (0);
}

int	fc_check_is_redirection(t_info *info)
{
	if (info->exe->nbr_pipe > 0
		|| info->exe->nbr_bracket_smaller_one > 0
		|| info->exe->nbr_bracket_smaller_two > 0
		|| info->exe->nbr_bracket_bigger_one > 0
		|| info->exe->nbr_bracket_bigger_two > 0)
			return (0);
	return (1);
}
*/