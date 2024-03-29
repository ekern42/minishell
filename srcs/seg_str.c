/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:26:39 by ekern             #+#    #+#             */
/*   Updated: 2023/03/16 15:11:31 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	fc_free_last_list(t_vars *info, t_quotes *temp)
{
	t_quotes	*temp2;

	temp2 = info->quotes_list;
	if (temp2->next == NULL)
		free (temp2);
	else
	{
		while (temp2->next != temp)
			temp2 = temp2->next;
		temp2->next = NULL;
		free (temp);
	}
}

static t_quotes	*fc_last_quote_list(t_vars *info)
{
	t_quotes	*temp;

	temp = info->quotes_list;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	fc_seg_str(t_vars *info)
{
	t_quotes	*temp;
	int			a;

	a = 0;
	info->small_str_list = NULL;
	while (info->lex->nbr_pair_sgl_q != 0 || info->lex->nbr_pair_dbl_q != 0)
	{
		temp = fc_last_quote_list(info);
		a = fc_small_str_with_quote(info, temp, a);
		if (temp->type == 39)
			info->lex->nbr_pair_sgl_q--;
		else if (temp->type == 34)
			info->lex->nbr_pair_dbl_q--;
		fc_free_last_list(info, temp);
	}
	fc_small_str_without_quote(info, temp, a);
	fc_final_seg(info);
}
