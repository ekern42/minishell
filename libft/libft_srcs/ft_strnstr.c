/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:31:22 by ekern             #+#    #+#             */
/*   Updated: 2021/10/14 12:32:43 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *rc, size_t n)
{
	size_t	a;
	size_t	b;
	size_t	c;

	a = 0;
	b = 0;
	c = -1;
	if (rc[0] == '\0')
		return ((char *)src);
	while (n > 0 && src[a] != '\0')
	{	
		if (src[a] == 0)
			return (NULL);
		while (rc[b] == src[a + b] && a + b < n)
		{
			if (rc[b + 1] == '\0')
				return ((char *)src + a);
			b++;
		}
		a++;
	}
	return (0);
}
