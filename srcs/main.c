/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/09/22 17:19:41 by ekern            ###   ########.fr       */
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

void	fc_quote_list_free(t_info *info)
{
	t_quotes	*free_time;
	t_quotes	*temp;

	free_time = info->quotes_list;
	while (free_time != NULL)
	{
		temp = free_time->next;
		free (free_time);
		free_time = temp;
	}
}

int	main(int ac, char **av, char **envp)
{
	t_info		info;
	t_lex_info	lex;
	t_quotes	*temp;

	info.seg_command_line = NULL;

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
//			fc_init_seg_cmd_line(&info);
			fc_parsing(&info);
			printf("Main apres\n");
			if (info.seg_command_line)
			{
//				
				fc_exit(&info);
//				fc_execution(&info);
			}
		}
		free(info.command_line);
		fc_quote_list_free(&info);
	}
//	fc_final_free(&info);
}
