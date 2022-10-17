/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 16:19:16 by ekern             #+#    #+#             */
/*   Updated: 2022/10/17 15:19:07 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_check_lex(t_info *info, int a)
{
	if (info->command_line[a + 1] == '\0')
	{
		info->lex->error = true;
		return (0);
	}
	if (info->command_line[a + 1] == ' ')
		a++;
	if (info->command_line[a + 1] == '|'
		|| info->command_line[a + 1] == '<'
		|| info->command_line[a + 1] == '>')
	{
		info->lex->error = true;
		return (0);
	}
	return (1);
}

void	fc_lexer(t_info *info)
{
	int	a;
	int	b;

	fc_init_lexer(info);
	a = -1;
	while (info->command_line[++a] != '\0' && info->lex->error == false)
	{
		a = fc_lex_quotes(info, a);
		if (info->command_line[a] == '$')
			fc_lex_variables(info);
		if (info->command_line[a] == '|')
			if (fc_lex_pipes(info, a) == 0)
				return ;
		if (info->command_line[a] == '<' || info->command_line[a] == '>')
		{
			b = fc_lex_redirections(info, a);
			if (b == 0)
				return ;
			else if (b == 2)
				a++;
		}
//		if (info->command_line[a] == '\0') si overflow decom
//			break ;
	}
}
