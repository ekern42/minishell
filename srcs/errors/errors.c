/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:35:18 by angelo            #+#    #+#             */
/*   Updated: 2022/09/17 16:52:06 by angelo           ###   ########.fr       */
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

int	fc_error_exe(char *error, int code_return)
{
	printf("ERROR : code_return = %d\n", code_return);
	perror(error);
	return (1);
}

int	fc_error_exe2(int code_return)
{
	printf("ERROR : code_return = %d\n", code_return);
	return (code_return);
}
