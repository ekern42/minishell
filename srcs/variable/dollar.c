/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:21:57 by ekern             #+#    #+#             */
/*   Updated: 2022/10/17 12:53:10 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static t_list	*fc_dollar_sec(t_list *sub_temp, t_info *info, char *str, int b)
{
	if (info->b->j < info->begin[b])
	{
		sub_temp = fc_sub_dollar(sub_temp, info, str,
				info->begin[b] - info->b->j);
		info->b->j = info->begin[b];
		info->b_sub_str = info->b->j;
	}
	if (info->b->j == info->begin[b])
	{
		sub_temp = fc_sub_dollar(sub_temp, info, str,
				(info->end[b] + 1) - info->begin[b]);
		info->b->j = info->end[b] + 1;
		info->b_sub_str = info->b->j;
	}
	return (sub_temp);
}

static void	fc_dollar(t_info *info, char *str, int n)
{
	t_list	*sub_temp;
	int		b;

	info->b->j = 0;
	b = 0;
	info->b_sub_str = 0;
	sub_temp = NULL;
	while (info->b->j < ft_strlen(str))
	{	
		if (info->b->j > info->end[b] && b < n)
			b++;
		else if (info->b->j > info->end[b] && b >= n)
		{
			sub_temp = fc_sub_dollar(sub_temp, info, str,
					ft_strlen(str) - info->b->j + 1);
			info->b->j = ft_strlen(str);
		}
		sub_temp = fc_dollar_sec(sub_temp, info, str, b);
	}
	fc_replace_dollar(info, sub_temp);
}

static int	fc_dollar_details2_sec(t_info *info, int a, int b, int c)
{
	if (info->begin[b] > c && info->end[b] < a)
	{
		info->begin[b] = -1;
		info->end[b] = -1;
	}
	b++;
	return (b);
}

static void	fc_dollar_details2(t_info *info, char *str, int n)
{
	int	a;
	int	b;
	int	c;

	a = -1;
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
			b = fc_dollar_details2_sec(info, a, b, c);
		if (str[a] == '\0')
			break ;
		c = a;
	}
	fc_dollar(info, str, n);
}

void	fc_dollar_details(t_info *info, char *str, int n)
{
	int	a;
	int	b;

	a = -1;
	b = 0;
	fc_malloc_dollar(info, n);
	while (str[++a] != '\0')
	{
		if (str[a] == '$')
		{
			info->begin[b] = a;
			while (str[++a] != '\0')
			{
				if (str[a] == '\'' || str[a] == '\"' || str[a] == '$')
				{
					info->end[b++] = a - 1;
					break ;
				}
			}
			if (str[a] == '\0')
				info->end[b++] = a - 1;
			a--;
		}
	}
	fc_dollar_details2(info, str, n);
}
