/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:44:16 by angelo            #+#    #+#             */
/*   Updated: 2022/09/25 18:14:49 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_parsing(t_info *info)
{
	int nbr_cmds;
	char ***temp;

//	printf("pipe %d\n", info->lex->nbr_pipe);
	temp= malloc(sizeof(char **) * (info->lex->nbr_pipe + 2));
	if (!temp)
		exit (0); // error a gerer
	nbr_cmds = info->lex->nbr_pipe + 1;
	temp[nbr_cmds] = NULL;
	info->exe->cmds = temp;
	fc_seg_str(info);

	return (0);
}
