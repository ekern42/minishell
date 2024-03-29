/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_info_utils_02.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:28:17 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:33:19 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
// bool	is_inside_double_realquote(t_quote_info *qti)
// {
// 	if (is_inside_realquote(qti) && qti->last_char_realquote == '\"')
// 		return (true);
// 	return (false);	
// }
// -------------------------------------------------
bool	is_inside_single_realquote(t_quote_info *qti)
{
	if (is_inside_realquote(qti) && qti->last_char_realquote == '\'')
		return (true);
	return (false);
}

/* ************************************************************************** */
bool	is_entering_realquote(t_quote_info *qti)
{
	if (qti->flag_entering_realquote)
		return (true);
	return (false);
}

// -------------------------------------------------
bool	is_exiting_realquote(t_quote_info *qti)
{
	if (qti->flag_exiting_realquote)
		return (true);
	return (false);
}

/* ************************************************************************** */
// To used in the same scope than: [ refresh_info_quote() ]
bool	is_inside_realquote(t_quote_info *qti)
{
	if (qti->flag_inside_realquote)
		return (true);
	return (false);
}

// -------------------------------------------------

bool	is_outside_realquote(t_quote_info *qti)
{
	if (qti->flag_inside_realquote)
		return (false);
	return (true);
}

/* ************************************************************************** */
