/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 09:51:45 by ekern             #+#    #+#             */
/*   Updated: 2021/10/20 09:52:33 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *src, void (*f)(unsigned int, char*))
{
	unsigned int	a;

	a = 0;
	if (src != NULL)
	{
		while (src[a] != '\0')
		{
			f(a, src + a);
			a++;
		}
	}
}
