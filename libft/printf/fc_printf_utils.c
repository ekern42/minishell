/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_printf_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:13:55 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:52:49 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	fc_putchar_printf(char c)
{
	write(1, &c, 1);
}

void	fc_putnbr_printf(unsigned int nbr)
{
	if (nbr < 10)
		fc_putchar_printf(nbr + '0');
	else
	{
		fc_putnbr_printf(nbr / 10);
		fc_putchar_printf((nbr % 10) + '0');
	}
}

int	fc_strlen_printf(const char *str)
{
	int	l;

	l = 0;
	while (*str++ != '\0')
		l++;
	return (l);
}
