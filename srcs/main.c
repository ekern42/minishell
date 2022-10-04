/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/10/04 10:55:12 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fc_prompt(t_info *info)
{
	info->command_line = readline("Minishell : ");
	if (!info->command_line)
		fc_control_d(info);
	else if (info->command_line[0] == '\0')
		fc_prompt(info);
	else
		add_history(info->command_line);
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_info		info;
	t_lex_info	lex;

	if (ac > 1 || av[1] != NULL)
		fc_error(&info, 1);
	fc_init(&info, &lex, envp);
	fc_signal(&info);
	while (1)
	{
		fc_init_lexer(&info);
		fc_prompt(&info);
		fc_lexer(&info);
		if (info.lex->error == false)
		{
			fc_parsing(&info);
			fc_exit(&info);
			//fc_print_cmds(&info);
			if (info.lex->pipes == false && info.lex->re_append == false)
				fc_execution(&info);
			else if (info.lex->pipes == true && info.lex->re_append == false)
				fc_exe_with_pipe(&info);
			else if (info.lex->re_append == true)
				fc_re_append(&info);
		}
		free(info.command_line);
//		fc_quote_list_free(&info);
	}
//	fc_final_free(&info);
}
