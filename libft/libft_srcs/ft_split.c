/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:48:20 by ekern             #+#    #+#             */
/*   Updated: 2022/04/05 14:42:05 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*fait plein de strings de la string princ avec le separateur c */

static int	fc_count_nbr_sstr(const char *src, char c)
{
	unsigned int	n;

	n = 0;
	while (*src == c && *src != '\0')
		src++;
	while (*src != '\0')
	{
		n++;
		while (*src != '\0' && *src != c)
			src++;
		while (*src != '\0' && *src == c)
			src++;
	}
	return (n);
}

static int	fc_count_sz_sstr(const char *src, char c)
{
	unsigned int	n;

	n = 0;
	while (*src != '\0' && *src != c)
	{
		n++;
		src++;
	}
	return (n);
}

char	**ft_split(const char *src, char c)
{
	char			**dest;
	unsigned int	nbr;
	unsigned int	n;
	unsigned int	a;
	unsigned int	b;

	if (src == NULL)
		return (NULL);
	nbr = fc_count_nbr_sstr(src, c);
	dest = (char **)malloc(sizeof(char *) * (nbr + 1));
	if (dest == NULL)
		return (NULL);
	a = 0;
	b = 0;
	while (nbr > b)
	{
		while (src[a] == c)
			a++;
		n = fc_count_sz_sstr(&src[a], c);
		dest[b] = ft_substr(&src[a], 0, n);
		a += n;
		b++;
	}
	dest[nbr] = NULL;
	return (dest);
}
/*
int	main(void)
{
	char	src[] = "ABCD.EFGH.IJKL.1265465654684634.9876";
	int	i;
	char	**str;
	
	i = 0;
	str = ft_split(src, '.');
	while (i < 5)
	{
		printf("%s\n", str[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		free (str[i]);
		i++;
	}
	free(str);
}*/