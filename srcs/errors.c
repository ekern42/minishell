/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/13 12:44:10 by gudias            #+#    #+#             */
/*   Updated: 2023/03/17 12:07:54 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void	err_msg(char *msg)
{
	ft_putendl_fd(msg, 2);
}

/* ************************************************************************** */
void	exit_msg(char *msg)
{
	err_msg(msg);
	exit(1);
}

/* ************************************************************************** */
int	manage_perror(char *remark, int error_code)
{
	perror(remark);
	ft_putstr_fd("\n", 2);
	return (error_code);
}

void	fc_error_lex(t_vars *info, char c)
{
	info->lex->error = true;
	ft_putstr("minishell : syntax error near token \'");
	ft_putchar(c);
	ft_putstr("\'\n");
	update_var(&info->loc, "?", "258");
}
