/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:31:19 by ekern             #+#    #+#             */
/*   Updated: 2022/10/17 14:01:08 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_small_str_common2_sec(t_info *info, int a)
{
	if (info->command_line[a + 1] != '<' && info->command_line[a + 1] != '>')
	{
		fc_sub_str(info, a + 1);
		info->b_sub_str = a + 1;
		a++;
	}
	else
	{
		if (info->command_line[a + 2] != ' ')
		{
			fc_sub_str(info, a + 2);
			info->b_sub_str = a + 2;
			a += 2;
		}
	}
	return (a);
}
