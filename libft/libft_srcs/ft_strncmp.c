/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 17:30:13 by ekern             #+#    #+#             */
/*   Updated: 2021/10/14 14:42:50 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			a;
	unsigned char	d1;
	unsigned char	d2;

	a = 0;
	if (n == 0)
		return (0);
	while (n > 0)
	{
		d1 = s1[a];
		d2 = s2[a];
		if (d1 != d2)
			return (d1 - d2);
		if (d1 == '\0')
			return (0);
		n--;
		a++;
	}
	return (0);
}
