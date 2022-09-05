/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:38 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 22:31:36 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fc_start_up(void)
{
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-----------MINISHELL-----------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
	ft_putstr_fd("-------------------------------\n", 1);
}

static void	fc_envp_init(t_info *info, char **envp)
{
	(void)info;
	(void)envp;
//	printf("|%s|\n", envp[0]);
}

int	fc_init(t_info *info, char **envp)
{
	fc_envp_init(info, envp);
	fc_start_up();
	return (0);
}
