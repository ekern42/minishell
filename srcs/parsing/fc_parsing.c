/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:44:16 by angelo            #+#    #+#             */
/*   Updated: 2022/10/01 09:53:44 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_parsing(t_info *info)
{
	int nbr_cmds;
	char ***temp;
//	int	a;
//	int	b;
	
//	printf("pipe %d\n", info->lex->nbr_pipe);
	temp= malloc(sizeof(char **) * (info->lex->nbr_pipe + 2));
	if (!temp)
		exit (0); // error a gerer
	nbr_cmds = info->lex->nbr_pipe + 1;
	temp[nbr_cmds] = NULL;
	info->exe->cmds = temp;
	fc_seg_str(info);
/*	printf("parsing finish\n");
	a = 0;
	while (a != info->lex->nbr_pipe + 1)
	{
		b = 0;
		while (info->exe->cmds[a][b] != NULL)
		{
			printf("%s\n", info->exe->cmds[a][b]);
			b++;
		}
			printf("----------\n");
		a++;
	} */
	return (0);
}

#include "../minishell.h"

int	fc_parsing2(t_info *info)
{
	fc_info_seg_cmd_line(info);
	return (0);
}
