/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_specprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 11:34:58 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:46:30 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	fc_countnbr(size_t nbr)
{
	int	t;

	t = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		nbr /= 16;
		t++;
	}
	return (t);
}

static char	*fc_tranhexa(char *str, int l, size_t nbr, int n)
{
	unsigned int	temp;
	int				t;

	t = 0;
	if (n == 0)
		t = 32;
	if (nbr == 0)
	{
		str[0] = '0';
		return (str);
	}
	while (nbr != 0)
	{
		l--;
		temp = nbr % 16;
		if (temp < 10)
			str[l] = temp + 48;
		else
			str[l] = temp + (55 + t);
		nbr /= 16;
	}
	return (str);
}

int	fc_pointer(va_list param)
{
	unsigned long long	a;
	int					c;
	int					l;
	char				*str;

	a = va_arg(param, unsigned long long);
	c = fc_countnbr(a);
	str = (char *) malloc(sizeof(char) * c + 1);
	if (str == NULL)
		return (0);
	str[c] = '\0';
	fc_tranhexa(str, c, a, 0);
	write(1, "0x", 2);
	l = fc_strlen_printf(str) + 2;
	c = 0;
	while (str[c] != '\0')
		fc_putchar_printf(str[c++]);
	free (str);
	return (l);
}

int	fc_hexa(va_list param, int n)
{
	char			*str;
	int				a;
	int				l;
	unsigned int	nbr;

	nbr = va_arg(param, unsigned int);
	a = fc_countnbr(nbr);
	str = malloc(sizeof(char) * a + 1);
	if (str == NULL)
		return (0);
	str[a] = '\0';
	fc_tranhexa(str, a, nbr, n);
	l = fc_strlen_printf(str);
	a = 0;
	while (str[a] != '\0')
		fc_putchar_printf(str[a++]);
	free (str);
	return (l);
}
