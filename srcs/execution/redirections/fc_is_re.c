/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_is_re.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 13:07:50 by aprosper          #+#    #+#             */
/*   Updated: 2022/10/15 13:08:21 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_is_re(t_info *info, int i, int fd)
{
	int	j;

	j = 0;
	info->exe->fd_re = fd;
	while (info->exe->cmds[i][j])
	{	
		if (ft_strncmp(info->exe->cmds[i][j], ">>", 3) == 0)
		{
			fc_re_append(info, i, j, info->exe->fd_re);
			break ;
		}
		else if (ft_strncmp(info->exe->cmds[i][j], ">", 2) == 0)
		{
			fc_re_output(info, i, j, info->exe->fd_re);
			break ;
		}
		else if (ft_strncmp(info->exe->cmds[i][j], "<", 2) == 0)
		{
			fc_re_input(info, i, j, info->exe->fd_re);
			break ;
		}
		j++;
	}
	return (0);
}