/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:24:46 by ekern             #+#    #+#             */
/*   Updated: 2022/09/06 13:53:47 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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
}
