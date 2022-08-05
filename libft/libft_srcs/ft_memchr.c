/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:30:16 by ekern             #+#    #+#             */
/*   Updated: 2021/10/13 17:30:58 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *mb, int sc, size_t n)
{
	const unsigned char	*src;

	src = (const unsigned char *)mb;
	while (n > 0)
	{
		if (*src == (unsigned char)sc)
			return ((void *)src);
		src++;
		n--;
	}
	return (NULL);
}
