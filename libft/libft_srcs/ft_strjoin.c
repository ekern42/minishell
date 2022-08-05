/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 13:08:27 by ekern             #+#    #+#             */
/*   Updated: 2021/10/15 13:36:05 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	int		a;
	int		b;
	char	*dest;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	a = ft_strlen(s1);
	b = ft_strlen(s2);
	dest = malloc(sizeof(*dest) * (a + b + 1));
	if (dest == NULL)
		return (NULL);
	a = 0;
	b = 0;
	while (s1[b] != '\0')
		dest[a++] = s1[b++];
	b = 0;
	while (s2[b] != '\0')
		dest[a++] = s2[b++];
	dest[a] = '\0';
	return (dest);
}
