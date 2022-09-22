/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:44:16 by angelo            #+#    #+#             */
/*   Updated: 2022/09/22 16:41:14 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_parsing(t_info *info)
{
	int nbr_cmds;

//	info->exe->cmds = (char ***)malloc(sizeof(char **) * info->lex->nbr_pipe + 2);
//	if (!info->exe->cmds)
//		exit (0); // error a gerer
	nbr_cmds = info->lex->nbr_pipe + 1;
//	info->exe->cmds[nbr_cmds] = NULL;
	info->b_sub_str = 0;
	while (nbr_cmds > 0)
	{
		fc_seg_str(info);
		nbr_cmds--;
	}

	return (0);
}
