/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 15:31:09 by ekern             #+#    #+#             */
/*   Updated: 2021/10/13 16:52:49 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *p1, const void *p2, size_t n)
{
	const unsigned char	*l1;
	const unsigned char	*l2;

	l1 = (const unsigned char *)p1;
	l2 = (const unsigned char *)p2;
	while (n > 0)
	{
		if (*l1 != *l2)
			return (*l1 - *l2);
		l1++;
		l2++;
		n--;
	}
	return (0);
}
