/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 15:38:34 by angelo            #+#    #+#             */
/*   Updated: 2022/10/10 12:30:40 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_exit(t_info *info)
{
	if (strncmp(*info->exe->cmds[0], "exit", 5) == 0)
	{
		fc_final_free(info);
		exit (127);
	}
	return (1);
}
