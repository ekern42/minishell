/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_line.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:25:51 by ekern             #+#    #+#             */
/*   Updated: 2022/09/06 15:22:08 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fc_nbr_of_small_str(t_info *info)
{
	int	nbr;
	int	a;
	
	nbr = 0;
	a = -1;
}

static char	**fc_perfect_split(t_info *info)
{
	int		nbr;

	if (!info->command_line)
		return (NULL);
	nbr = fc_nbr_of_small_str(info);
}

void	fc_split_line(t_info *info)
{
	info->seg_command_line = ft_split(info->command_line, ' ');
//	fc_perfect_split(info);
	if (!info->seg_command_line)
		fc_error(info, 2);
		
}
