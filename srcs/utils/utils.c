/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:37 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 22:32:25 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

size_t	fc_strlen(const char *str)
{
	int	a;

	a = 0;
	while (str[a] != ' ' && str[a] != '\0')
		a++;
	return (a);
}

void	fc_test(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
		printf("{%d}%s{%d}\n", i, envp[i], i);
}

void	fc_exit(t_info *info)
{
	if (info->seg_command_line)
		fc_free_seg_command_line(info);
	ft_putstr_fd("exit command\n", 1);
	exit (0);
}
