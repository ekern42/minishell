/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lex_quotes.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:24:46 by ekern             #+#    #+#             */
/*   Updated: 2023/03/16 15:28:44 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fc_quote_list_free(t_vars *info)
{
	t_quotes	*temp;

	temp = info->quotes_list->next;
	while (temp)
	{
		free (info->quotes_list);
		info->quotes_list = temp;
		temp = info->quotes_list->next;
	}
}

/*
static void	fc_free_one_chain(t_vars *info)
{
	t_quotes	*temp;

	temp = info->quotes_list->next;
	free (info->quotes_list);
	info->quotes_list = temp;
}
*/

static void	fc_init_quote_list(t_vars *info, int a, char c)
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

int	fc_lex_quotes(t_vars *info, int a)
{
	int		b[2];
	char	c;

	b[0] = a;
	b[1] = 0;
	if (info->command_line[a] == '\'' || info->command_line[a] == '\"')
	{
		c = info->command_line[a];
		b[1] = 1;
	}
	if (b[1] == 1)
	{
		fc_init_quote_list(info, a, c);
		while (info->command_line[++b[0]] != c)
		{
			if (info->command_line[b[0]] == '\0')
			{
				info->lex->error = true;
				fc_quote_list_free(info);
				return (a + 1);
			}
		}
		info->quotes_list->end = b[0];
		if (c == '\'')
			info->lex->nbr_pair_sgl_q++;
		else if (c == '\"')
			info->lex->nbr_pair_dbl_q++;
	}
	return (b[0]);
}
