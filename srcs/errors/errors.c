/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:35:18 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 11:11:40 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_error(t_info *info, int a)
{
	(void)info;
	if (a == 1)
		ft_putstr_fd("Too much args\n", 1);
	else if (a == 2)
		ft_putstr_fd("Split error\n", 1);
//	fc_final_free(info);
	exit (0);
}

int	fc_error_exe(int code_return, char *error_message)
{
	//printf("%s\n", error_message);
	perror(error_message);
	//printf("Error :\ncode return = %d | %s\n", code_return, error_message);
	return (code_return);
}

int	fc_putstr_fd_error(char *str, t_info *info)
{
	while (*str)
		write(2, str++, 1);
	if (info->exe->path)
		while (*info->exe->path)
			write(2, info->exe->path++, 1);
	write(2, "\n", 1);
	return (1);
}

void	fc_error_message(t_info *info, int i)
{
	if (i == 1)
	{
		write(2, "Minishell: ", 11);
		write(2, info->exe->cmds[0][2], ft_strlen(info->exe->cmds[0][2]));
		write (2, ": No such file or directory\n", 28);
	}

	else if (i == 2)
	{
		ft_putstr_fd("Minishell: syntax error ", 2);
		ft_putstr_fd("near unexpected token `newline'\n", 2);
	}
	


}
