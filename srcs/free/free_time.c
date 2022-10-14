/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_time.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/11 10:45:01 by ekern             #+#    #+#             */
/*   Updated: 2022/10/14 14:25:51 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

/* free t_list tres particulier */
void	fc_free_t_list_spec(t_info *info)
{
	t_list	*free_time;
	t_list	*temp;
	int		a;

	free_time = info->small_str_list;
	a = 0;
	while (free_time && a != 1)
	{
		if (!ft_strncmp(free_time->content, "|", 1))
			a = 1;
		temp = free_time->next;
		free (free_time->content);
		free (free_time);
		free_time = temp;
	}
	info->small_str_list = free_time;
}

/* free cmds */
void	fc_final_free(t_info *info)
{
	int	a;
	int	b;
	int	c;

	a = 0;
	b = 0;
	free(info->command_line);
	if (!info->exe->cmds)
		return ;
	while (a <= (info->lex->nbr_pipe + 1))
	{
		if (info->exe->cmds[a] != NULL)
		{
			c = fc_dblstrlen(info->exe->cmds[a]);
			while (b <= c)
			{
				free(info->exe->cmds[a][b]);
				b++;
			}
		}
		b = 0;
		free(info->exe->cmds[a]);
		a++;
	}
	free(info->exe->cmds);
}
