/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:22:55 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:46:44 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *src, ...)
{
	va_list	param;
	int		l[3];

	va_start(param, src);
	l[2] = 0;
	l[0] = 0;
	while (*src != '\0')
	{
		if (*src == '%')
		{
			l[1] = fc_check(*++src, param);
			if (l[1] >= 0)
			{
				src++;
				l[0] += l[1];
			}
		}
		else
		{
			fc_putchar_printf(*src++);
			l[2]++;
		}
	}
	va_end (param);
	return (l[2] + l[0]);
}
