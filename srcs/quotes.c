/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 11:24:46 by ekern             #+#    #+#             */
/*   Updated: 2022/08/16 12:00:41 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void fc_dbl_quotes(t_info *info)
{
	ft_putstr_fd("double quotes\n", 1);
}

static void fc_sgl_quotes(t_info *info)
{
	ft_putstr_fd("single quotes\n", 1);
}

int fc_quotes(t_info *info)
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
	if (sgl_quote / 2 == 1)
		fc_sgl_quotes(info);
	else if (dbl_quote / 2 == 1)
		fc_dbl_quotes(info);
	else
		return (1);
	return (2);
}
