/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 14:07:21 by ekern             #+#    #+#             */
/*   Updated: 2022/09/01 14:32:22 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void fc_exit(t_info *info)
{
	if (info->seg_command_line)
		fc_free_seg_command_line(info);
	ft_putstr_fd("exit command\n", 1);
	exit (0);
}

int	fc_command(t_info *info)
{
	if (strncmp(info->seg_command_line[0], "echo", 5) == 0)
		ft_putstr_fd("echo\n", 1);
	else if (strncmp(info->seg_command_line[0], "cd", 3) == 0)
		ft_putstr_fd("cd\n", 1);
	else if (strncmp(info->seg_command_line[0], "pwd", 4) == 0)
		ft_putstr_fd("pwd\n", 1);
	else if (strncmp(info->seg_command_line[0], "export", 7) == 0)
		ft_putstr_fd("export\n", 1);
	else if (strncmp(info->seg_command_line[0], "unset", 6) == 0)
		ft_putstr_fd("unset\n", 1);
	else if (strncmp(info->seg_command_line[0], "env", 4) == 0)
		ft_putstr_fd("env\n", 1);
	else if (strncmp(info->seg_command_line[0], "exit", 5) == 0)
		fc_exit(info);
	else if (fc_check_variable(info) == 1)
		fc_variable_command(info);
	else
		ft_putstr_fd("error : command not found\n", 1);
	fc_free_seg_command_line(info);
	return (0);
}

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