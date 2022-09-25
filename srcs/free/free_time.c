/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:45:01 by ekern             #+#    #+#             */
/*   Updated: 2022/09/25 15:03:34 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_quote_list_free(t_info *info)
{
	t_quotes	*free_time;
	t_quotes	*temp;

	free_time = info->quotes_list;
	while (free_time != NULL)
	{
		temp = free_time->next;
		free (free_time);
		free_time = temp;
	}
}

void	fc_free_seg_command_line(t_info *info)
{
	int	a;

	a = -1;
	while (info->seg_command_line[++a] != NULL)
		free(info->seg_command_line[a]);
}

void	fc_free_t_list(t_info *info)
{
	t_list	*free_time;
	t_list	*temp;

	free_time = info->small_str_list;
	while (free_time != NULL)
	{
		temp = free_time->next;
		free (free_time);
		free_time = temp;
	}
}
/*
void	fc_final_free(t_info *info)
{
	fc_free_seg_command_line(info);
}
*/