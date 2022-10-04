/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/10/04 13:12:25 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_execution(t_info *info)
{
	if (info->lex->pipes == false
	&& info->lex->re_append == false
	&& info->lex->re_input == false
	&& info->lex->re_del == false
	&& info->lex->re_input == false)
		fc_exe_without_re(info);
	else if (fc_check_is_redir(info) == 0 && info->lex->pipes == false) // provisoire, pour : >>
		fc_re_append(info);
	else if (info->lex->pipes == true)
		fc_exe_with_re(info); // with pipes
	return (0);
}

//if (fc_builtins(info) != 0 || fc_execution_cmd(info) != 0)
//{
//	ft_putstr_fd("error : command not found\n", 1);
//	fc_free_seg_command_line(info);
//}
