/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execution.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/10 13:00:45 by angelo            #+#    #+#             */
/*   Updated: 2022/10/12 15:34:07 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_init_idx(t_info *info)
{
	if (info->lex->pipes == true)
		info->idx_re = 1;
	else
		info->idx_re = 0;
	return (0);
}

int	fc_execution(t_info *info)
{
	int	i;

	i = 0;
	//fc_init_idx(info);
	info->exe->tmp_fd = dup(STDIN_FILENO);
	if (info->exe->tmp_fd == -1)
		fc_error_exe(1, "dup");
	while (i < info->lex->nbr_pipe + 1)
	{
		//printf("i = %d\n", i);
		if (i == info->lex->nbr_pipe)
			fc_is_last_command(info, i);
		else // envoie l'output dans un pipe
			fc_not_in_last_command(info, i);
		i++;
	}
	if (close(info->exe->tmp_fd) == -1)
		fc_error_exe(1, "close");
	return (0);
}
