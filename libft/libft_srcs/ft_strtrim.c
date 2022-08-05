/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/15 14:31:36 by ekern             #+#    #+#             */
/*   Updated: 2021/10/20 11:46:12 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(const char *s1, const char *set)
{
	int		len;
	char	*dest;

	if (s1 == NULL)
		return (NULL);
	while (*s1 != '\0' && ft_strchr(set, *s1) != NULL)
		s1++;
	len = ft_strlen((char *)s1);
	while (len > 0 && ft_strchr(set, s1[len - 1]) != NULL)
		len --;
	dest = malloc(sizeof(char) * len + 1);
	if (dest == NULL)
		return (NULL);
	ft_memmove(dest, s1, len);
	dest[len] = '\0';
	return (dest);
}
