/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_fork_child.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:33:26 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void	init_struct_sa_fork_child(t_sig *s);
static void	init_sigaction_fork_child(t_sig *s);
static void	init_struct_sa_fork_child_hd(t_sig *s);

/* ************************************************************************** */
void	init_signal_fork_child(t_sig *s)
{
	init_struct_sa_fork_child(s);
	init_sigaction_fork_child(s);
}

/* ************************************************************************** */
static void	init_struct_sa_fork_child(t_sig *s)
{
	s->sa_sigint.sa_handler = SIG_DFL;
	s->sa_sigquit.sa_handler = SIG_DFL;
}

/* ************************************************************************** */
static void	init_sigaction_fork_child(t_sig *s)
{
	sigaction(SIGINT, &s->sa_sigint, NULL);
	sigaction(SIGQUIT, &s->sa_sigquit, NULL);
}

/* ************************************************************************** */
void	init_signal_fork_child_hd(t_sig *s)
{
	init_struct_sa_fork_child_hd(s);
	init_sigaction_fork_child(s);
}

/* ************************************************************************** */
static void	init_struct_sa_fork_child_hd(t_sig *s)
{
	s->sa_sigint.sa_handler = SIG_DFL;
	s->sa_sigquit.sa_handler = SIG_IGN;
}
/* ************************************************************************** */