/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_pipes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:42:54 by ekern             #+#    #+#             */
/*   Updated: 2022/10/07 16:31:55 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_lex_pipes(t_info *info, int a)
{
	int	b;
	int	c;

	b = a;
	c = a;
	while (--b > 0 && info->command_line[b] == ' ');
	while (info->command_line[++c] != '\0' && info->command_line[c] == ' ');
	if (a == 0 || b == 0 || info->command_line[c] == '\0')
	{
		info->lex->error = true;
		return (0);
	}
//	if (fc_check_lex(info, a) == 0)
//		return (0);
	info->lex->nbr_pipe++;
	info->lex->pipes = true;
	return (1);
}
