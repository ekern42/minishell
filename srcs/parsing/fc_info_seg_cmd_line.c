/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_info_seg_cmd_line.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 20:10:41 by angelo            #+#    #+#             */
/*   Updated: 2022/09/20 17:29:14 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_info_seg_cmd_line(t_info *info)
{
	int	i;

	info->lex->nbr_pipe = 0;
	info->lex->nbr_re_input = 0;
	info->lex->nbr_re_del = 0;
	info->lex->nbr_re_output = 0;
	info->lex->nbr_re_append = 0;
	i = 0;
	while (info->seg_command_line[++i] != NULL)
	{
		if (strncmp(info->seg_command_line[i], "|", 2) == 0)
			info->lex->nbr_pipe++; //return (1);
		else if (strncmp(info->seg_command_line[i], "<", 2) == 0)
			info->lex->nbr_re_input++;
		else if (strncmp(info->seg_command_line[i], "<<", 3) == 0)
			info->lex->nbr_re_del++;
		else if (strncmp(info->seg_command_line[i], ">", 2) == 0)
			info->lex->nbr_re_output++;
		else if (strncmp(info->seg_command_line[i], ">>", 3) == 0)
			info->lex->nbr_re_append++;
	}
	info->exe->size_seg_cmd_line = i;
	/*printf("nbr | : %d\n", info->lex->nbr_pipe);
	printf("nbr < : %d\n", info->lex->nbr_re_input);
	printf("nbr << : %d\n", info->lex->nbr_re_del);
	printf("nbr > : %d\n", info->lex->nbr_re_output);
	printf("nbr >> : %d\n", info->lex->nbr_re_append);
	printf("size_seg_cmd_line : %d\n", info->exe->size_seg_cmd_line);*/
	return (0);
}
