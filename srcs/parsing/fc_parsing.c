/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:44:16 by angelo            #+#    #+#             */
/*   Updated: 2022/10/04 13:21:26 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_parsing(t_info *info)
{
	int nbr_cmds;
	char ***temp;

	temp= malloc(sizeof(char **) * (info->lex->nbr_pipe + 2));
	if (!temp)
		exit (0); // error a gerer
	nbr_cmds = info->lex->nbr_pipe + 1;
	temp[nbr_cmds] = NULL;
	info->exe->cmds = temp;
	fc_seg_str(info);
	fc_print_for_pipe(info);
	return (0);
}

void	fc_print_for_pipe(t_info *info)
{
	int	a;
	int	b;

	printf("pipe = %d\n", info->lex->nbr_pipe);
	a = 0;
	while (a != info->lex->nbr_pipe + 1)
	{
		b = 0;
		while (info->exe->cmds[a][b] != NULL)
		{
			printf("%s\n", info->exe->cmds[a][b]);
			b++;
		}
//			printf("----------\n");
		a++;
	}
}
