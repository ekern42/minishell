/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_minishell.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/08/09 17:20:37 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fc_command(t_info *info)
{
	if (strncmp(info->command_line, "echo", 5) == 0)
		ft_putstr_fd("echo\n", 1);
	else if (strncmp(info->command_line, "cd", 3) == 0)
		ft_putstr_fd("cd\n", 1);
	else if (strncmp(info->command_line, "pwd", 4) == 0)
		ft_putstr_fd("pwd\n", 1);
	else if (strncmp(info->command_line, "export", 7) == 0)
		ft_putstr_fd("export\n", 1);
	else if (strncmp(info->command_line, "unset", 6) == 0)
		ft_putstr_fd("unset\n", 1);
	else if (strncmp(info->command_line, "env", 4) == 0)
		ft_putstr_fd("env\n", 1);
	else if (strncmp(info->command_line, "exit", 5) == 0)
		ft_putstr_fd("exit\n", 1);
	else
		ft_putstr_fd("Syntax error\n", 1);
	return (0);
}

int	fc_prompt(t_info *info)
{
	info->command_line = readline("Minishell : ");
	return (1);
}

int	main(int ac, char **av, char **envp)
{
	t_info info;

	if (ac > 1 || av[1] != NULL)
		fc_error(1);
	fc_init(&info);
	fc_signal(&info);
	while(1)
	{
		fc_prompt(&info);
		if (info.command_line == NULL)
			fc_control_d();
		fc_command(&info);
		
	}
	
}