/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/12 16:23:16 by ekern             #+#    #+#             */
/*   Updated: 2021/10/13 14:10:44 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	if (c == 0)
		return ((char *)s);
	else if (*s == '\0')
		return (NULL);
	return ((char *)s);
}
/*
int	main(void)
{
	char	s[] = "Salut";
	
	printf("%s\n", ft_strchr(s, 'S' + 256));
}*/