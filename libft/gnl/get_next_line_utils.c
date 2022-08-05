/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:12:32 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:53:22 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	fc_strlen_gnl(const char *str)
{
	int	a;

	a = 0;
	if (str == NULL)
		return (0);
	while (str[a] != '\0')
		a++;
	return (a);
}

char	*fc_strndup_gnl(const char *src, size_t l)
{
	size_t	a;
	char	*dest;

	dest = malloc(sizeof(*dest) * l + 1);
	if (dest == NULL)
		return (NULL);
	a = 0;
	while (a < l)
	{
		dest[a] = src[a];
		a++;
	}
	dest[a] = '\0';
	return (dest);
}

char	*fc_strjoin_gnl(char *s1, char *s2)
{
	int		a;
	int		b;
	char	*dest;	

	if (s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		s1[0] = '\0';
	}
	if (s2 == NULL || s1 == NULL)
		return (NULL);
	a = fc_strlen_gnl(s1);
	b = fc_strlen_gnl(s2);
	dest = malloc(sizeof(char) * (a + b + 1));
	if (dest == NULL)
		return (NULL);
	dest[a + b] = '\0';
	a = -1;
	b = 0;
	while (s1[++a] != '\0')
		dest[a] = s1[a];
	free (s1);
	while (s2[b] != '\0')
		dest[a++] = s2[b++];
	return (dest);
}

int	fc_strchr_gnl(const char *s, int c)
{
	while (*s != '\0' && *s != (char)c)
		s++;
	if (c == 0)
		return (1);
	else if (*s == '\0')
		return (0);
	return (1);
}
