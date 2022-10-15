/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:21:57 by ekern             #+#    #+#             */
/*   Updated: 2022/10/15 18:05:45 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
static void	fc_dollar_details2(char *str, int *begin, int *end, int n)
{
	int	a;
	int	b;
	int	c;

	a = -1;
//	printf("begin be %d, end be %d\n", begin[0], end[0]);
//	printf("begin be %d, end be %d\n", begin[1], end[1]);
//	printf("begin be %d, end be %d\n", begin[2], end[2]);
//	ft_putstr_fd("---------------\n", 1);
	while (str[++a] != '\0')
	{
		b = 0;
		if (str[a] == '\'')
		{
			c = a;
			while (str[++a] != '\'' && str[a] != '\0')
				;
			if (str[a] == '\0')
				c = a;
		}
		while (b < n)
		{
			if (begin[b] > c && end[b] < a)
			{
				begin[b] = -1;
				end[b] = -1;
			}
			b++;
		}
		if (str[a] == '\0')
			break ;
		c = a;
	}
	printf("begin af %d, end af %d\n", begin[0], end[0]);
//	printf("begin af %d, end af %d\n", begin[1], end[1]);
//	printf("begin af %d, end af %d\n", begin[2], end[2]);
}

static void	fc_dollar_details(t_info *info, char *str, int n)
{
	int	*begin;
	int	*end;
	int	a;
	int	b;

	a = -1;
	b = 0;
	begin = ft_calloc(sizeof(int), (n + 1));
	end = ft_calloc(sizeof(int), (n + 1));
	if (!begin || !end)
		exit (0); // erreur a faire, malloc
	while (str[++a] != '\0')
	{
		if (str[a] == '$')
		{
			begin[b] = a;
			while (str[++a] != '\0')
			{
				if (str[a] == '\'' || str[a] == '\"' || str[a] == '$')
				{
					end[b++] = a - 1;
					break ;
				}
			}
			if (str[a] == '\0')
				end[b++] = a - 1;
			a--;
		}
	}
//	printf("begin %d, end %d\n", begin[0], end[0]);
	fc_dollar_details2(str, begin, end, n);
}

void	fc_check_dollar(t_info *info, char *str)
{
	int	a;
	int	b;

	a = -1;
	b = 0;
	while (str[++a] != '\0')
	{
		if (str[a] == '$')
			b++;
	}
	if (b > 0)
		fc_dollar_details(info, str, b);
}