/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_info_utils_01.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/04 10:28:17 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:33:12 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
static bool	is_quote_char(char c);

/* ************************************************************************** */
// Need: variable of type [ t_quote_info ]
void	init_quote_info(t_quote_info *qti)
{
	qti->cnt_char_realquote = 0;
	qti->last_char_realquote = '\0';
	qti->flag_inside_realquote = false;
	qti->flag_entering_realquote = false;
	qti->flag_exiting_realquote = false;
}

/* ************************************************************************** */
// To use under the while (...) statement ONLY once
void	refresh_quote_info(t_quote_info *qti, char actual_char)
{
	qti->flag_entering_realquote = false;
	if (qti->flag_exiting_realquote == true)
		init_quote_info(qti);
	if (is_quote_char(actual_char))
	{
		if (qti->flag_inside_realquote == false)
		{
			qti->last_char_realquote = actual_char;
			qti->cnt_char_realquote++;
			qti->flag_inside_realquote = true;
			qti->flag_entering_realquote = true;
		}
		else
		{
			if (qti->last_char_realquote == actual_char)
			{
				qti->last_char_realquote = '\0';
				qti->cnt_char_realquote++;
				qti->flag_exiting_realquote = true;
			}			
		}
	}
}

/* ************************************************************************** */
bool	is_line_with_correct_quote(char *line, t_vars *vars)
{
	int				i;	
	t_quote_info	qti;

	init_quote_info(&qti);
	i = 0;
	while (line[i] != '\0')
	{
		refresh_quote_info(&qti, line[i]);
		i++;
	}	
	if (is_good_number_of_realquote(&qti))
		return (true);
	ft_printf("minishell: syntax error in quoting line\n");
	update_var(&vars->loc, "?", "1");
	return (false);
}

/* ************************************************************************** */
// To used with: [ refresh_info_quote() ]
bool	is_good_number_of_realquote(t_quote_info *qti)
{
	if (qti->cnt_char_realquote % 2 == 0)
		return (true);
	return (false);
}

/* ************************************************************************** */
static bool	is_quote_char(char c)
{
	if (c == '\'' || c == '\"')
		return (true);
	return (false);
}

/* ************************************************************************** */
