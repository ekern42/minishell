/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:44:16 by angelo            #+#    #+#             */
/*   Updated: 2023/03/17 10:36:11 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fc_parsing(t_vars *info)
{
	int		nbr_cmds;
	char	***temp;

	if (info->lex->error == false)
	{
		temp = malloc(sizeof(char **) * (info->lex->nbr_pipe + 2));
		if (!temp)
			return (0);
		nbr_cmds = info->lex->nbr_pipe + 1;
		temp[nbr_cmds] = NULL;
		info->exe->cmds = temp;
		fc_seg_str(info);
	}
	else
	{
		info->exe->cmds = NULL;
	}
	return (0);
}
