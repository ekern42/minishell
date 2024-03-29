/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 15:33:28 by angelo            #+#    #+#             */
/*   Updated: 2023/03/17 12:24:48 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fc_init_lexer(t_vars *info)
{
	info->b_sub_str = 0;
	info->nbr_sstr = 0;
	info->quotes_list = NULL;
	info->lex->pipes = false;
	info->lex->nbr_pipe = 0;
	info->lex->sgl_quotes = false;
	info->lex->nbr_pair_sgl_q = 0;
	info->lex->dbl_quotes = false;
	info->lex->nbr_pair_dbl_q = 0;
	info->lex->variable = false;
	info->lex->nbr_variable = 0;
	info->lex->re_append = false;
	info->lex->nbr_re_append = 0;
	info->lex->re_del = false;
	info->lex->nbr_re_del = 0;
	info->lex->re_input = false;
	info->lex->nbr_re_input = 0;
	info->lex->re_output = false;
	info->lex->nbr_re_output = 0;
	info->lex->error = false;
}

int	fc_init(t_vars *info)
{
	info->lex = malloc(sizeof(t_lex_info));
	info->exe = malloc(sizeof(t_execution));
	return (0);
}
