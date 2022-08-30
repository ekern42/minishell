/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:31:22 by ekern             #+#    #+#             */
/*   Updated: 2022/08/26 12:07:53 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *src, const char *rc, size_t n)
{
	size_t	a;
	size_t	b;

	a = 0;
	b = 0;
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
