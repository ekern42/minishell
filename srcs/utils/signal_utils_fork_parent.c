/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils_fork_parent.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/15 09:09:38 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:33:33 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
static void	init_struct_sa_fork_parent(t_sig *s);
static void	init_sigaction_fork_parent(t_sig *s);

/* ************************************************************************** */
void	init_signal_fork_parent(t_sig *s)
{
	init_struct_sa_fork_parent(s);
	init_sigaction_fork_parent(s);
}

/* ************************************************************************** */
static void	init_struct_sa_fork_parent(t_sig *s)
{
	s->sa_sigint.sa_handler = &handler_signal_fork_parent;
	s->sa_sigint.sa_flags = SA_RESTART;
	s->sa_sigquit.sa_handler = SIG_IGN;
}

/* ************************************************************************** */
static void	init_sigaction_fork_parent(t_sig *s)
{
	sigaction(SIGINT, &s->sa_sigint, NULL);
	sigaction(SIGQUIT, &s->sa_sigquit, NULL);
}

/* ************************************************************************** */
void	handler_signal_fork_parent(int sig_code)
{
	if (sig_code == SIGINT)
	{	
		ft_putstr_fd("\n", 2);
	}
}

/* ************************************************************************** */
