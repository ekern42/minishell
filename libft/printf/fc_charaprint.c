/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_charaprint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:25:53 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:45:28 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	fc_char(va_list param)
{
	char	c;

	c = va_arg(param, int);
	fc_putchar_printf(c);
	return (1);
}

int	fc_string(va_list param)
{
	char	*str;
	int		l;

	str = va_arg(param, char *);
	if (str == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	l = fc_strlen_printf(str);
	while (*str != '\0')
		fc_putchar_printf(*str++);
	return (l);
}
