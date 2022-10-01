/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/10/01 10:41:12 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
Makefile :
- CFLAGS = -Werror -Wextra -Wall
- #-g3 -fsanitize=address

void	fc_small_str_without_quote(t_info *info, t_quotes *temp, int a)
- (void)temp;

static void	fc_size_seg_str(t_info *info)
- //	char	*content_temp;
- //	content_temp = NULL;

void fc_final_seg(t_info *info)
- // exit ; // erreur a faire -> remplacé par : exit(1);

static void test(t_info *info)
- Toute la fonction mis en commentaire

int	main(int ac, char **av, char **envp)
- //	t_quotes	*temp;
- //	fc_parsing(&info); -> sinon mes trucs temporaires ne fonctionnent pas !
*/

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
//	t_quotes	*temp;

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
//			fc_parsing(&info);
			fc_init_seg_cmd_line2(&info);
			if (info.seg_command_line)
			{
				fc_parsing2(&info);
				fc_exit(&info);
				if (info.exe->nbr_pipe == 0 && info.exe->nbr_bracket_bigger_two == 0) // without redirection
					fc_execution(&info);
				else if (info.exe->nbr_pipe == 1 && info.exe->nbr_bracket_bigger_two == 0) // with : |
					fc_exe_with_pipe(&info);
				else if (info.exe->nbr_bracket_bigger_two == 1) // with : >>
					fc_double_bracket_big_to_small(&info);
			}
		}
		free(info.command_line);
//		fc_quote_list_free(&info);
	}
//	fc_final_free(&info);
}
