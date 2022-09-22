/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:44:17 by ekern             #+#    #+#             */
/*   Updated: 2022/09/22 17:22:24 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	fc_sub_str(t_info *info, int a)
{
	char	*str_temp;
	t_list	*list_temp;

	list_temp = info->small_str_list;
	str_temp = ft_substr(info->command_line, info->b_sub_str, a - info->b_sub_str);
	ft_lstadd_back(&list_temp, ft_lstnew(str_temp));
	info->small_str_list = list_temp;
}
/* b_sub_str = premier charactere apres un space, a = space de fin de str ou '\0' */
int	fc_small_str_with_quote(t_info *info, t_quotes *temp, int a)
{
//	ft_putstr_fd("substr av\n", 1);
	while (info->command_line[a] != temp->begin)
	{
		while (info->command_line[info->b_sub_str] == ' ')	//b_sub decaler de 1 par rapport a 'a'
		{
			info->b_sub_str++;
			a++;
		}
		if (info->command_line[a] == ' ')
		{
			fc_sub_str(info, a);
			info->b_sub_str = a; // mettre a + 1 en cas de probleme de decalage
		}
		a++;
	}
	a = temp->end;
//	ft_putstr_fd("substr ap\n", 1);
	return (a);
}

void	fc_small_str_without_quote(t_info *info, t_quotes *temp, int a)
{
	while (info->command_line[a] != '\0' && info->command_line[a] != '|')
	{
		while (info->command_line[info->b_sub_str] == ' ')
		{
			info->b_sub_str++;
			a++;
		}
		if (info->command_line[a] == ' ' || info->command_line[a] == '|')
		{
			fc_sub_str(info, a);
			info->b_sub_str = a;	
		}
		a++;
	}
	if (info->command_line[a] == '\0')
		fc_sub_str(info, a);
}