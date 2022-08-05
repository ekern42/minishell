/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:11:42 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:44:14 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

/*
1 - 
Doit lire tout la ligne jusqu'au \n
le buffer fait le nombre d'etape
renvoie ligne par ligne jusqu'a la fin du doc
*/

static char	*fc_clean_src(char *src)
{
	int		n;
	int		l;
	char	*clnsrc;

	if (src[0] == '\0')
	{
		free (src);
		return (NULL);
	}
	n = 0;
	while (src[n] != '\n')
	{
		if (src[n] == '\0')
			break ;
		n++;
	}
	l = fc_strlen_gnl(src);
	clnsrc = fc_strndup_gnl((src + n + 1), (l - n));
	free (src);
	return (clnsrc);
}

static char	*fc_strline(const char *src)
{
	int		n;
	char	*strfinal;

	if (src[0] == '\0')
		return (NULL);
	n = 0;
	while (src[n] != '\0')
	{
		if (src[n] == '\n')
		{
			n++;
			break ;
		}
		n++;
	}
	strfinal = fc_strndup_gnl(src, n);
	return (strfinal);
}

static char	*fc_read(int fd, char *src)
{
	char	*str;
	int		n;
	int		l;

	str = malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (str == NULL)
		return (NULL);
	n = 0;
	l = 1;
	while (n == 0 && l != 0)
	{
		l = read(fd, str, BUFFER_SIZE);
		if (l == -1)
		{
			free (str);
			return (NULL);
		}
		str[l] = '\0';
		src = fc_strjoin_gnl(src, str);
		n = fc_strchr_gnl(str, '\n');
	}
	free (str);
	return (src);
}

char	*get_next_line(int fd)
{
	static char	*src;
	char		*strfinal;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	src = fc_read(fd, src);
	if (src == NULL)
		return (NULL);
	strfinal = fc_strline(src);
	src = fc_clean_src(src);
	return (strfinal);
}
