/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:44:17 by ekern             #+#    #+#             */
/*   Updated: 2023/03/16 15:05:28 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fc_sub_str(t_vars *info, int a)
{
	char	*str_temp;
	t_list	*list_temp;

	list_temp = info->small_str_list;
	str_temp = ft_substr(info->command_line,
			info->b_sub_str, a - info->b_sub_str);
	ft_lstadd_back(&list_temp, ft_lstnew(str_temp));
	info->small_str_list = list_temp;
}

static int	fc_small_str_common2(t_vars *info, int a)
{
	if (a != 0)
	{
		if ((info->command_line[a] == '<' || info->command_line[a] == '>')
			&& info->command_line[a - 1] != ' ')
		{
			if (info->command_line[a - 1] != '<'
				&& info->command_line[a - 1] != '>')
			{
				fc_sub_str(info, a);
				info->b_sub_str = a;
			}
		}
	}
	if ((info->command_line[a] == '<' || info->command_line[a] == '>')
		&& info->command_line[a + 1] != ' ')
		a = fc_small_str_common2_sec(info, a);
	return (a);
}

int	fc_small_str_common(t_vars *info, int a)
{
	while (info->command_line[info->b_sub_str] == ' ')
	{
		info->b_sub_str++;
		a++;
	}
	if (info->command_line[a] == ' ')
	{
		fc_sub_str(info, a);
		info->b_sub_str = a + 1;
	}	
	if (a != 0)
	{
		if (info->command_line[a - 1] != ' ' && info->command_line[a] == '|')
		{
			fc_sub_str(info, a);
			info->b_sub_str = a;
		}
	}
	a = fc_small_str_common2(info, a);
	return (a);
}

int	fc_small_str_with_quote(t_vars *info, t_quotes *temp, int a)
{
	while (a != temp->begin)
	{
		a = fc_small_str_common(info, a);
		if (a != temp->begin)
		{
			if (info->command_line[a + 1] != ' '
				&& info->command_line[a] == '|')
			{
				fc_sub_str(info, a + 1);
				info->b_sub_str = a + 1;
			}
			a++;
		}
	}
	a = temp->end;
	return (a);
}

void	fc_small_str_without_quote(t_vars *info, t_quotes *temp, int a)
{
	(void)temp;
	while (info->command_line[a] != '\0')
	{
		a = fc_small_str_common(info, a);
		if (info->command_line[a] != '\0')
		{
			if (info->command_line[a + 1] != ' '
				&& info->command_line[a] == '|')
			{
				fc_sub_str(info, a + 1);
				info->b_sub_str = a + 1;
			}
			a++;
		}
	}
	if (info->command_line[a] == '\0'
		&& info->command_line[a - 1] != ' ')
	{
		if (info->command_line[a - 1] != '>'
			&& info->command_line[a - 1] != '<')
		{
			fc_sub_str(info, a);
			info->nbr_sstr++;
		}
	}
}
