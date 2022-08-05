/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:14:56 by ekern             #+#    #+#             */
/*   Updated: 2021/11/23 12:34:07 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	int					a;
	unsigned char		*text;
	const unsigned char	*sourc;

	if (src == NULL && dest == NULL)
		return (NULL);
	a = 0;
	text = dest;
	sourc = src;
	while (n > 0)
	{
		text[a] = sourc[a];
		a++;
		n--;
	}
	return (text);
}
