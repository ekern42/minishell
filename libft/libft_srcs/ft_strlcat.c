/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:30:44 by ekern             #+#    #+#             */
/*   Updated: 2021/10/14 17:31:05 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t n)
{
	size_t	a;
	size_t	b;
	size_t	c;
	size_t	d;

	a = ft_strlen(dest);
	b = ft_strlen(src);
	if (n == 0)
		return (b);
	else if (a >= n)
		return (n + b);
	else
	{
		c = a;
		d = 0;
		while (c < (n - 1) && src[d] != '\0')
		{
			dest[c] = src[d];
			d++;
			c++;
		}
		dest[c] = '\0';
		return (a + b);
	}
}
