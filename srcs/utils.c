/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:37 by ekern             #+#    #+#             */
/*   Updated: 2023/03/16 15:26:27 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fc_dblstrlen(char **tab)
{
	int	a;

	a = 0;
	while (tab[a] != NULL)
		a++;
	return (a);
}
