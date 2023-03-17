/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 14:38:31 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:31:56 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* ************************************************************************** */
int	pwd_builtin(t_vars *vars, char **cmd_args)
{
	char	cwd_name[CWD_BUF_SIZE];

	(void)vars;
	(void)cmd_args;
	if (getcwd(cwd_name, CWD_BUF_SIZE) == NULL)
		return (manage_perror("pwd_builtin", errno));
	else
		ft_printf("%s\n", cwd_name);
	return (BUILTIN_SUCCESS);
}

/* ************************************************************************** */
