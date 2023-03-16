/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:34:50 by gudias            #+#    #+#             */
/*   Updated: 2023/03/16 15:06:41 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	update_return_code(t_vars *vars, int return_code)
{
	char	*buff;

	buff = ft_itoa(return_code);
	update_var(&vars->loc, "?", buff);
	ft_free_null(&buff);
}

void	handle_segments(t_vars *vars, char ***segments)
{
	int	i;

	i = 0;
	vars->segments_count = vars->lex->nbr_pipe + 1;
	while (segments[i + 1])
		parse_line(vars, segments[i++], 0);
	parse_line(vars, segments[i], 1);
	dup2(vars->stdin_fd, 0);
	vars->segments_count = 0;
}

void	parse_line(t_vars *vars, char **line, int output)
{
	t_cmd	cmd;
	int		i;
	int		return_code;
	int		a;

	a = -1;
	return_code = 0;
	cmd.args = line;
	if (!(cmd.args) || !(cmd.args[0]))
	{
		free_array(cmd.args);
		return ;
	}
	get_redirections(vars, &cmd);
	if (!cmd.fd_out)
		cmd.fd_out = output;
	i = check_assignations(vars, &cmd);
	return_code = execute_cmd(vars, &cmd, i);
	update_return_code(vars, return_code);
	init_signal_main(&vars->sig);
	reset_redirections(vars, &cmd);
	free_array(cmd.args);
}
