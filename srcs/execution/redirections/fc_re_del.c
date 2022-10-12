/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:18:29 by ekern             #+#    #+#             */
/*   Updated: 2022/10/12 11:47:36 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_re_del(t_info *info, int a, int i)
{
	char	*del;
	char	*line;

	if (ft_strncmp(info->exe->cmds[i][a], "<<", 3) == 0)
	{
		line = readline("> ");
		del = info->exe->cmds[i][a + 1];
		while (ft_strncmp(line, del, 5) != 0)
		{
			free(line);
//			fc_stockage();
			line = readline("> ");
		}
//		fc_re_input();
		free(line);
		return (1);
	}
	return (0);
}