/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_redirections.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/20 09:47:40 by ekern             #+#    #+#             */
/*   Updated: 2022/10/12 15:30:45 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fc_lex_sgl_red(t_info *info, int a)
{
	if (info->command_line[a] == '>')
	{
		info->lex->re_output = true;
		info->lex->nbr_re_output++;
	}
	else if (info->command_line[a] == '<')
	{
		info->lex->re_input = true;
		info->lex->nbr_re_input++;
	}
}

static void	fc_lex_dbl_red(t_info *info, int a)
{
	if (info->command_line[a] == '<')
	{
		info->lex->re_del = true;
		info->lex->nbr_re_del++;
	}
	else if (info->command_line[a] == '>')
	{
		info->lex->re_append = true;
		info->lex->nbr_re_append++;
	}
}

static int	fc_check_red(t_info *info, int a)
{
	while (info->command_line[++a] == ' ' && info->command_line[a] != '\0');
	if (info->command_line[a] == '\0')
		return (1);
	else if (info->command_line[a] == '<' || info->command_line[a] == '>')
	{
		info->lex->error = true;
		return (0);
	}
	return (1);
}

int	fc_lex_redirections(t_info *info, int a)
{
	if (info->command_line[a] == info->command_line[a + 1])
	{
		fc_lex_dbl_red(info, a);
		if (fc_check_red(info, a + 1) == 0)
			return (0);
		return (2);
	}
	else
	{
		fc_lex_sgl_red(info, a);
		if (fc_check_red(info, a) == 0)
			return (0);
		return (1);
	}
}
