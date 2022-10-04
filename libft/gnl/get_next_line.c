/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/09 11:11:42 by ekern             #+#    #+#             */
/*   Updated: 2022/10/03 16:27:16 by angelo           ###   ########.fr       */
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
/*
int main(void)
{
	char	*str;
	int		fd;
	str = NULL;
	fd = open("42", O_RDONLY);
	if (fd == -1)
	{
		printf("open() failed\n");
		return (1);
	}
	str = get_next_line(fd);
	while (str != (void *)0)
	{
		printf("%s", str);
		str = get_next_line(fd);
	}
	if (close(fd) == 1)
	{
		printf("close() failed\n");
		return (1);
	}
	return (0);
}
*/