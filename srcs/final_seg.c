/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_seg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:11:47 by ekern             #+#    #+#             */
/*   Updated: 2023/03/16 16:18:35 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*fc_sstr_change(char *content_temp)
{
	int		a;
	int		b;
	int		size_sstr;
	char	*sstr_temp;

	size_sstr = ft_strlen(content_temp);
	sstr_temp = malloc(sizeof (char ) * size_sstr + 1);
	if (!sstr_temp)
		return (NULL);
	a = 0;
	b = 0;
	while (content_temp[a] != '\0')
	{
		sstr_temp[b++] = content_temp[a++];
	}
	sstr_temp[b] = '\0';
	return (sstr_temp);
}

static void	fc_size_seg_str(t_vars *info)
{
	t_list	*temp;

	temp = info->small_str_list;
	info->b_sub_str = 0;
	while (temp && ft_strncmp(temp->content, "|", 1))
	{
		info->b_sub_str++;
		temp = temp->next;
	}
}

void	fc_final_seg(t_vars *info)
{
	t_list	*temp;
	char	*content_temp;
	char	**seg_temp;
	int		a;
	int		b;

	b = 0;
	while (info->small_str_list)
	{
		fc_size_seg_str(info);
		a = 0;
		temp = info->small_str_list;
		seg_temp = malloc(sizeof(char *) * (info->b_sub_str + 1));
		if (!seg_temp)
			return ;
		seg_temp[info->b_sub_str] = NULL;
		while (temp && ft_strncmp(temp->content, "|", 1))
		{
			content_temp = fc_sstr_change(temp->content);
			seg_temp[a++] = content_temp;
			temp = temp->next;
		}
		info->exe->cmds[b++] = seg_temp;
		fc_free_t_list_spec(info);
	}
}
