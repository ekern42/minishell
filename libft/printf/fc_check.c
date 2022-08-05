/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 10:17:21 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:45:36 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fc_check(const char c, va_list param)
{
	int	len;

	if (c == 'c')
		len = fc_char(param);
	else if (c == 's')
		len = fc_string(param);
	else if (c == 'p')
		len = fc_pointer(param);
	else if (c == 'd' || c == 'i')
		len = fc_decim(param);
	else if (c == 'u')
		len = fc_unsint(param);
	else if (c == 'x')
		len = fc_hexa(param, 0);
	else if (c == 'X')
		len = fc_hexa(param, 1);
	else if (c == '%')
	{
		fc_putchar_printf('%');
		len = 1;
	}
	else
		len = -1;
	return (len);
}
