/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:11:06 by ekern             #+#    #+#             */
/*   Updated: 2021/10/20 12:44:16 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	int	a;

	a = ft_strlen((char *)s);
	while (s[a] != c && a > 0)
		a--;
	if (s[a] == (char)c)
		return ((char *)s + a);
	return (NULL);
}
/*
int	main(void)
{
	char	s[] = "Salut";
	char	s2[] = "SalUt";
	printf("%s\n", ft_strrchr(s, 'S' + 256));
}*/