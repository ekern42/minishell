/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_print_chainlist.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 15:42:48 by ekern             #+#    #+#             */
/*   Updated: 2022/09/06 12:35:24 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	fc_print_chainlist(t_list *lst, char letter, int fd)
{
	while (lst)
	{
		if (letter == 'c' || letter == 's')
			ft_putstr_fd((char *)lst->content, fd);
		else if (letter == 'd' || letter == 'i')
			ft_putnbr_fd((long)lst->content, fd);
		else
			ft_putstr_fd("Only 'c', 's', 'd' or 'i' accepted in second arg\n", 1);
		if (lst->next)
			ft_putstr_fd(" -> ", fd);
		lst = lst->next;
	}
	ft_putchar_fd('\n', fd);
}
