/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/10/17 12:54:11 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fc_prompt(t_info *info)
{
	info->command_line = readline("\033[1;36mMinishell :\033[0m");
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

	if (ac > 1 || av[1] != NULL)
		fc_error(&info, 1);
	fc_init(&info, envp);
	fc_signal(&info);
	while (1)
	{
		fc_prompt(&info);
		fc_lexer(&info);
		if (info.lex->error == false)
		{
			fc_parsing(&info);
			if (info.exe->cmds)
			{
				fc_exit(&info);
				if(fc_check_variable(&info, 0, 0) == 0)
					fc_execution(&info);
			}
		}
		fc_print_var_list(&info);
		fc_final_free(&info);
	}
}
