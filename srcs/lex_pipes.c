/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:42:54 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:08:07 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fc_lex_pipes(t_vars *info, int a)
{
	int	b;
	int	c;

	b = a;
	c = a;
	while (--b > 0 && info->command_line[b] == ' ')
		;
	while (info->command_line[++c] != '\0' && info->command_line[c] == ' ')
		;
	if (a == 0 || b == 0 || info->command_line[c] == '\0')
	{
		fc_error_lex(info, info->command_line[a]);
		return (0);
	}
	info->lex->nbr_pipe++;
	info->lex->pipes = true;
	return (1);
}
