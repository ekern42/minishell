/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 17:06:58 by ekern             #+#    #+#             */
/*   Updated: 2021/10/15 12:05:02 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t n)
{
	unsigned char	*dest;
	size_t			a;

	a = 0;
	dest = malloc(count * n);
	if (dest == NULL)
		return (NULL);
	while (a < (count * n))
	{
		dest[a] = '\0';
		a++;
	}
	return (dest);
}
