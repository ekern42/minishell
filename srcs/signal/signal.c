/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 15:45:43 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 11:25:22 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void fc_control_d(t_info *info)
{
	ft_putstr_fd("Exit D\n", 1);
	exit (0);
}

static void fc_control_backslash(int num)
{
	ft_putstr_fd("\nBackSlashed\n", 1);
}

static void fc_control_c(int num)
{
	ft_putstr_fd("\nDenied\n", 1);
}

int	fc_signal(t_info *info)
{
	signal(SIGINT, fc_control_c);
	signal(SIGQUIT, fc_control_backslash);
	return (1);
}