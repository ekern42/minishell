/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:38 by ekern             #+#    #+#             */
/*   Updated: 2022/08/11 14:42:39 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void fc_start_up(void)
{
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-----------MINISHELL-----------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
}

static void fc_envp_init(t_info *info, char **envp)
{
//	printf("|%s|\n", envp[0]);
}

int	fc_init(t_info *info, char **envp)
{
	fc_envp_init(info, envp);
	fc_start_up();
	return (0);
}