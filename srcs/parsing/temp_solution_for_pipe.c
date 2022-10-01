/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   temp_solution_for_pipe.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:20:36 by angelo            #+#    #+#             */
/*   Updated: 2022/09/27 11:42:59 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_size_for_create_substr(t_info *info)
{
	int	i;

	i = 0;
	while (info->seg_command_line[i] != NULL)
	{
		if (strncmp(info->seg_command_line[i], "|", 2) == 0
			|| strncmp(info->seg_command_line[i], ">", 2) == 0
			|| strncmp(info->seg_command_line[i], ">>", 3) == 0
			|| strncmp(info->seg_command_line[i], "<", 2) == 0
			|| strncmp(info->seg_command_line[i], "<<", 3) == 0)
				return (i);
		i++;
	}
	return (i);
}

void	*fc_create_left_str(t_info *info)
{
	char	**str_left;
	int	i;
	int	j;

	i = fc_size_for_create_substr(info);
	//printf("i = %d\n", i);
	str_left = malloc(sizeof(char *) * (i + 1)); // checker plus tard

	i = 0;
	j = 0;
	while (info->seg_command_line[j] != NULL)
	{
		if (strncmp(info->seg_command_line[i], "|", 2) == 0
		|| strncmp(info->seg_command_line[i], ">", 2) == 0
		|| strncmp(info->seg_command_line[i], ">>", 3) == 0
		|| strncmp(info->seg_command_line[i], "<", 2) == 0
		|| strncmp(info->seg_command_line[i], "<<", 3) == 0)
			break ;
		str_left[i] = info->seg_command_line[j];
		i++;
		j++;
	}
	str_left[i] = NULL;

	// check is created ?
	//i = 0;
	//while (str_left[i] != NULL)
	//{
	//	printf("str_left[i] = %s\n", str_left[i]);
	//	i++;
	//}
	//printf("str_left[i] = %s\n", str_left[i]);
	return (str_left);
}

void	*fc_create_right_str(t_info *info)
{
	char	**str_right;
	int	i;
	int	j;

	i = fc_size_for_create_substr(info);
	if (i != info->exe->size_seg_cmd_line)
		str_right = malloc(sizeof(char *) * (info->exe->size_seg_cmd_line - i) + 5); // checker plus tard
	j = fc_size_for_create_substr(info) + 1; // pr sauter le char de redirection
	//printf("j = %d\n", j);
	
	i = 0;
	j = fc_size_for_create_substr(info) + 1;
	while (info->seg_command_line[j] != NULL)
	{
		str_right[i] = info->seg_command_line[j];
		i++;
		j++;
	}
	str_right[i] = NULL;
	
	// check is created ?
	//i = 0;
	//while (str_right[i] != NULL)
	//{
	//	printf("str_right[i] = %s\n", str_right[i]);
	//	i++;
	//}
	//printf("str_right[i] = %s\n", str_right[i]);
	return (str_right);
}
