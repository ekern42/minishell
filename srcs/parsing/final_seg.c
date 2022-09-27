/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   final_seg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/26 15:11:47 by ekern             #+#    #+#             */
/*   Updated: 2022/09/27 17:43:50 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static char *fc_sstr_change(char *content_temp)
{
	int		a;
	int		b;
	int		size_sstr;
	char	*sstr_temp;

	size_sstr = ft_strlen(content_temp);
	a = -1;
	while (content_temp[++a] != '\0')
		if (content_temp[a] == 39 || content_temp[a] == 34)
			size_sstr--;
	sstr_temp = malloc(sizeof (char ) * size_sstr + 1);
	if (!sstr_temp)
		exit (0); // erreur a faire
	a = 0;
	b = 0;
	while (content_temp[a] != '\0')
	{
		if (content_temp[a] == 39 || content_temp[a] == 34)
			a++;
		else
			sstr_temp[b++] = content_temp[a++];
	}
	sstr_temp[b] = '\0';
	return (sstr_temp);
}

void fc_final_seg(t_info *info)
{
	t_list	*temp;
	char	*content_temp;
	int		a;
	
	temp = info->small_str_list;
	while (temp)
	{
		content_temp = (char *)temp->content;
//		fc_size_seg_str(info);
		a = 0;
		while (content_temp[0] != '|' && temp)
		{
			content_temp = (char *)temp->content;
			content_temp = fc_sstr_change(content_temp);
//			fc_seg_init(info, a);
		
			printf("%s\n", content_temp);
			a++;
			temp = temp->next;
		}
	}
}