/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 17:52:30 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fc_check_is_pipe(t_info *info)
{
	if (info->lex->pipes == true)
		info->idx_re = 1;
	else
		info->idx_re = 0;
}

int	fc_execution(t_info *info)
{
	fc_check_is_pipe(info);
	if (fc_check_is_redir(info) == 0 && info->lex->pipes == false) // provisoire, pour : >>
		fc_re_append(info);
	else
		fc_exe_with_re(info);
	return (0);
}

//if (fc_builtins(info) != 0 || fc_execution_cmd(info) != 0)
//{
//	ft_putstr_fd("error : command not found\n", 1);
//	fc_free_seg_command_line(info);
//}
