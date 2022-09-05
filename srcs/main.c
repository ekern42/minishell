/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 13:13:28 by ekern            ###   ########.fr       */
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
	t_info info;

	info.seg_command_line = NULL;
	if (ac > 1 || av[1] != NULL)
		fc_error(&info, 1);
//	fc_test(envp);
	fc_init(&info, envp);
	fc_signal(&info);
	while(1)
	{
		fc_prompt(&info);
		if (fc_quotes(&info) == 1)
			fc_split_line(&info);
		if (info.seg_command_line)
			fc_command(&info);
		free(info.command_line);
	}
	fc_final_free(&info); 
}