/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 11:31:25 by ekern             #+#    #+#             */
/*   Updated: 2022/03/02 16:55:56 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* copie la string depuis la fin pour tout resoudre*/

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned int		a;
	unsigned char		*des;
	const unsigned char	*sr;

	a = 0;
	if (dest == NULL && src == NULL)
		return (NULL);
	if (dest > src)
	{
		des = dest + n;
		sr = src + n;
		while (n-- > 0)
			*--des = *--sr;
	}
	else
	{
		des = dest;
		sr = src;
		while (a != n)
		{
			des[a] = sr[a];
			a++;
		}
	}
	return (des);
}
/*
int	main(void)
{
	char	str[] = "ABCDEF";
	char	str2[] = "ABCDEF";
	
	ft_memmove((str + 2), str, 4);
	printf("move %s\n", str);
	ft_memcpy((str2 + 2), str2, 4);
	printf("cpy %s\n", str2);
}*/
