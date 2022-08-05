/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_nbrprint.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:26:16 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:45:46 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	fc_countnbr(unsigned int nbr)
{
	int	l;

	if (nbr == 0)
		return (1);
	l = 0;
	while (nbr > 0)
	{
		nbr /= 10;
		l++;
	}
	return (l);
}

int	fc_decim(va_list param)
{
	int				a;
	int				l;
	unsigned int	nbr;

	a = va_arg(param, int);
	nbr = a;
	l = 0;
	if (a < 0)
	{
		write(1, "-", 1);
		l += 1;
		nbr = -a;
	}
	l += fc_countnbr(nbr);
	fc_putnbr_printf(nbr);
	return (l);
}

int	fc_unsint(va_list param)
{
	unsigned int	nbr;
	int				l;

	nbr = va_arg(param, unsigned int);
	l = fc_countnbr(nbr);
	fc_putnbr_printf(nbr);
	return (l);
}
