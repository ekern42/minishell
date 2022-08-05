/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:51:38 by ekern             #+#    #+#             */
/*   Updated: 2022/03/17 15:16:39 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_countnbr(unsigned int n)
{
	int	l;

	if (n == 0)
		return (1);
	l = 0;
	while (n > 0)
	{
		n /= 10;
		l++;
	}
	return (l);
}

static int	ft_negativenbr(int n)
{
	if (n < 0)
		return (1);
	else
		return (0);
}

static int	ft_intneg(int n)
{
	unsigned int	l;

	l = n;
	if (n < 0)
		l = -n;
	return (l);
}

char	*ft_itoa(int n)
{
	char			*dest;
	unsigned int	a[3];

	a[1] = ft_negativenbr(n);
	a[2] = ft_intneg(n);
	a[0] = (ft_countnbr(a[2]) + a[1]);
	dest = malloc(sizeof(char) * (a[0] + 1));
	if (dest == NULL)
		return (NULL);
	dest[a[0]] = '\0';
	if (n == 0)
		dest[0] = '0';
	if (a[1] == 1)
		dest[0] = '-';
	while (a[2] > 0)
	{
		a[0]--;
		dest[a[0]] = (a[2] % 10 + '0');
		a[2] /= 10;
	}
	return (dest);
}
/*
int	main(void)
{
	char *test;

	test = ft_itoa(-65646);
	printf("%s\n", test);
	free (test);
}*/
