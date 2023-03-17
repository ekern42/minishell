/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 17:15:58 by gudias            #+#    #+#             */
/*   Updated: 2023/03/17 12:01:06 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_vars	g_vars;

int	main(int argc, char **argv, char **envp)
{
	if (argc > 1 || argv[1])
		exit_msg(ERR_ARGS);
	initialisation (&g_vars, envp);
	while (1)
	{
		g_vars.new_line = show_prompt(&g_vars);
		if (g_vars.new_line && *(g_vars.new_line))
		{
			g_vars.command_line = g_vars.new_line;
			add_history(g_vars.new_line);
			fc_lexer(&g_vars);
			fc_parsing(&g_vars);
			if (g_vars.exe->cmds)
				handle_segments(&g_vars, g_vars.exe->cmds);
		}
		if (g_vars.new_line == NULL)
		{
			clean_program(&g_vars);
			exit_msg("exit");
		}
		ft_free_null(&g_vars.new_line);
	}
	clean_program(&g_vars);
	return (0);
}
