/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_str_redir.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 18:01:49 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 16:30:45 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_check_is_redir(t_info *info)
{
	if (info->lex->nbr_re_append == true
	|| info->lex->re_output == true
	|| info->lex->re_del == true
	|| info->lex->re_input == true)
		return (0);
	return (1);
}

int	fc_size_str(t_info *info)
{
	int	i;
	
	i = 0;
	while (info->exe->cmds[info->idx_re][i])
	{
		if (strncmp(info->exe->cmds[info->idx_re][i], ">>", 3) == 0
		|| strncmp(info->exe->cmds[info->idx_re][i], ">", 2) == 0
		|| strncmp(info->exe->cmds[info->idx_re][i], "<<", 3) == 0
		|| strncmp(info->exe->cmds[info->idx_re][i], ">", 2) == 0)
			return (i);
		i++;
	}
	return (i);
}

void	*fc_create_left_str(t_info *info)
{
	int	i;

	if (fc_check_is_redir(info) == 1)
		return (NULL);
	info->exe->str_left = NULL;
	info->exe->str_left = malloc(sizeof(char *) * (fc_size_str(info) + 1));
	if (info->exe->str_left == NULL)
		fc_error_tmp(1, "Problem with malloc\n");

	i = 0;
	while (info->exe->cmds[info->idx_re][i] != NULL)
	{
		if (strncmp(info->exe->cmds[info->idx_re][i], ">>", 3) == 0
		|| strncmp(info->exe->cmds[info->idx_re][i], ">", 2) == 0
		|| strncmp(info->exe->cmds[info->idx_re][i], "<<", 3) == 0
		|| strncmp(info->exe->cmds[info->idx_re][i], "<", 3) == 0)
			break ;
		info->exe->str_left[i] = info->exe->cmds[info->idx_re][i];
		i++;
	}
	info->exe->str_left[i] = NULL;
	//fc_print_str_left(info);
	return (info->exe->str_left);
}

void	fc_print_str_left(t_info *info)
{
	int	i;

	i = 0;
	while (info->exe->str_left[i] != NULL)
	{
		printf("str_left[i] = %s\n", info->exe->str_left[i]);
		i++;
	}
	printf("str_left[i] = %s\n", info->exe->str_left[i]);
}
