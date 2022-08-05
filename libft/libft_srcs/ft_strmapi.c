/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:50:10 by ekern             #+#    #+#             */
/*   Updated: 2021/10/22 15:47:21 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *src, char (*f)(unsigned int, char))
{
	unsigned int	a;
	char			*dest;

	if (src == NULL)
		return (NULL);
	a = ft_strlen(src);
	dest = malloc(sizeof(char) * a + 1);
	if (dest == NULL)
		return (NULL);
	dest[a] = '\0';
	a = 0;
	while (src[a] != '\0')
	{
		dest[a] = f (a, src [a]);
		a++;
	}
	return (dest);
}
