/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:24:46 by ekern             #+#    #+#             */
/*   Updated: 2022/09/22 16:54:02 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fc_free_one_chain(t_info *info)
{
	t_quotes	*temp;

	temp = info->quotes_list->next;
	free (info->quotes_list);
	info->quotes_list = temp;
}

static void	fc_init_quote_list(t_info *info, int a, char c)
{
	t_quotes	*temp;

	temp = malloc(sizeof(t_quotes));
	if (!temp)
		exit (0); // erreur a faire
	temp->type = c;
	temp->begin = a;
	temp->next = info->quotes_list;
	info->quotes_list = temp;
}

int	fc_lex_quotes(t_info *info, int a)
{
	if (info->command_line[a] == 39) // single quote '
	{
		info->lex->nbr_pair_sgl_q++;
		fc_init_quote_list(info, a, 39);
		while (info->command_line[++a] != 39)
		{
			if (info->command_line[a] == '\0')
			{
				info->lex->nbr_pair_sgl_q--;
				fc_free_one_chain(info);
				return (a);
			}
		}
		info->quotes_list->end = a;
	}
	else if (info->command_line[a] == 34) // double quote "
	{
		info->lex->nbr_pair_dbl_q++;
		fc_init_quote_list(info, a, 34);
		while (info->command_line[++a] != 34)
		{
			if (info->command_line[a] == '\0')
			{
				info->lex->nbr_pair_dbl_q--;
				fc_free_one_chain(info);
				return (a);
			}
		}
		info->quotes_list->end = a;
	}
	return (a);
}

/*
int	fc_quotes(t_info *info)
{
	int	i;
	int	sgl_quote;
	int	dbl_quote;
	i = -1;
	sgl_quote = 0;
	dbl_quote = 0;
	while (info->command_line[++i] != '\0')
	{
		
		if (info->command_line[i] == 39) // single quote '
			sgl_quote++;
		else if (info->command_line[i] == 34) // double quote "
			dbl_quote++;
	}
	
	info->pair_sgl_quotes = sgl_quote / 2;
	info->pair_dbl_quotes = dbl_quote / 2;
//	printf("sgl : %d dbl : %d\n", info->pair_sgl_quotes, info->pair_dbl_quotes);
	return (0);
}
*/