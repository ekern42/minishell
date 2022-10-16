/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 10:21:57 by ekern             #+#    #+#             */
/*   Updated: 2022/10/16 16:50:46 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_dollar_fusion(t_info *info, t_list *sub)
{
	t_list	*sub_temp;
	char	*str;
	char	*str_temp;

	sub_temp = sub;
	str_temp = ft_strdup(sub_temp->content);
	sub_temp = sub_temp->next;
	while (sub_temp)
	{
		str = ft_strjoin(str_temp, sub_temp->content);
		free(str_temp);
		str_temp = ft_strdup(str);
		free(str);
		sub_temp = sub_temp->next;
	}
	printf("str_temp %s\n", str_temp);
	free (info->small_str_list->content);
	info->small_str_list->content = str_temp;
}

static void	fc_dollar(t_info *info, char *str, int n)
{
	t_list	*sub_temp;
	int		a;
	int		b;
	int		l;

	a = 0;
	b = 0;
	l = 0;
	info->b_sub_str = 0;
	sub_temp = NULL;
	while (a < ft_strlen(str) && l < 30)
	{	
		if (a > info->end[b] && b < n)
			b++;
		else if (a > info->end[b] && b >= n)
		{
			sub_temp = fc_sub_dollar(sub_temp, info, str, ft_strlen(str) - a + 1);
			a = ft_strlen(str);
		}
		if (a < info->begin[b])
		{
			sub_temp = fc_sub_dollar(sub_temp, info, str, info->begin[b] - a);
			a = info->begin[b];
			info->b_sub_str = a;
		}
		if (a == info->begin[b])
		{
			sub_temp = fc_sub_dollar(sub_temp, info, str, (info->end[b] + 1) - info->begin[b]);
			a = info->end[b] + 1;
			info->b_sub_str = a;
		}
		l++;
	}
	fc_replace_dollar(info, sub_temp);
//	fc_print_chainlist(sub_temp, 's', 1);
}

static void	fc_dollar_details2(t_info *info, char *str, int n)
{
	int	a;
	int	b;
	int	c;

	a = -1;
//	printf("info->begin be %d, info->end be %d\n", info->begin[0], info->end[0]);
//	printf("info->begin be %d, info->end be %d\n", info->begin[1], info->end[1]);
//	printf("info->begin be %d, info->end be %d\n", info->begin[2], info->end[2]);
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
			if (info->begin[b] > c && info->end[b] < a)
			{
				info->begin[b] = -1;
				info->end[b] = -1;
			}
			b++;
		}
		if (str[a] == '\0')
			break ;
		c = a;
	}
//	printf("info->begin af %d, info->end af %d\n", info->begin[0], info->end[0]);
//	printf("info->begin af %d, info->end af %d\n", info->begin[1], info->end[1]);
//	printf("info->begin af %d, info->end af %d\n", info->begin[2], info->end[2]);
	fc_dollar(info, str, n);
}

static void	fc_dollar_details(t_info *info, char *str, int n)
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