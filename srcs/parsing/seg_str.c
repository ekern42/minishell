/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   seg_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 16:26:39 by ekern             #+#    #+#             */
/*   Updated: 2022/09/25 18:26:50 by ekern            ###   ########.fr       */
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
	a = 0;
	b = 0;
	while (content_temp[a] != '\0')
	{
		if (content_temp[a] == 39 || content_temp[a] == 34)
			a++;
		else
		{
			sstr_temp[b] = content_temp[a];
			b++;
			a++;
		}
	}
	sstr_temp[b] = '\0';
	return (sstr_temp);
}

static void fc_final_seg(t_info *info)
{
	t_list	*temp;
	char	*content_temp;
	char	*sstr_temp;
	
	temp = info->small_str_list;
	while (temp)
	{
		content_temp = (char *)temp->content;
		sstr_temp = fc_sstr_change(content_temp);
		printf("%s\n", sstr_temp);
		temp = temp->next;
	}
}

static void fc_free_last_list(t_info *info, t_quotes *temp)
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

static t_quotes *fc_last_quote_list(t_info *info)
{
	t_quotes	*temp;

	temp = info->quotes_list;
	while (temp->next != NULL)
		temp = temp->next;
	return (temp);
}

void	fc_seg_str(t_info *info)
{
	t_quotes *temp;
	char	**seg_cmd;
	int	a;

	a = info->b_sub_str;
	info->small_str_list = NULL;
//	printf("beg %d\n", info->b_sub_str);
//	printf("dbl %d / sgl %d\n", info->lex->nbr_pair_dbl_q, info->lex->nbr_pair_sgl_q);
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
//	fc_print_chainlist(info->small_str_list, 's', 1);
	fc_final_seg(info);
	fc_free_t_list(info);
}
