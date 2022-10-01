/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sub_str.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/22 14:44:17 by ekern             #+#    #+#             */
/*   Updated: 2022/10/01 10:20:18 by angelo           ###   ########.fr       */
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

int	fc_small_str_common(t_info *info, int a)
{
	while (info->command_line[info->b_sub_str] == ' ') //common
	{
		info->b_sub_str++;
		a++;
//		printf("while space with\n");
	}
	if (info->command_line[a] == ' ') //common
	{
		fc_sub_str(info, a);
		info->b_sub_str = a + 1;
//		printf("1 if with\n");
	}	
	if (a != 0) // common
		if (info->command_line[a - 1] != ' ' && info->command_line[a] == '|')
		{
			fc_sub_str(info, a);
			info->b_sub_str = a;
//			printf("2 if with\n");
		}
	return (a);
}

int	fc_small_str_with_quote(t_info *info, t_quotes *temp, int a)
{

	while (a != temp->begin)
	{
		a = fc_small_str_common(info, a);
		if (a != temp->begin)
		{
			if (info->command_line[a + 1] != ' ' && info->command_line[a] == '|')
			{
				fc_sub_str(info, a + 1);
				info->b_sub_str = a + 1;
//				printf("3 if with\n");
			}
			a++;
		}
	}
	a = temp->end; 
	
	return (a);
} 

void	fc_small_str_without_quote(t_info *info, t_quotes *temp, int a)
{
	(void)temp;
	while (info->command_line[a] != '\0')
	{
		a = fc_small_str_common(info, a);
		if (info->command_line[a] != '\0')
		{
			if (info->command_line[a + 1] != ' ' && info->command_line[a] == '|')
			{
				fc_sub_str(info, a + 1);
				info->b_sub_str = a + 1;
//				printf("3 if out\n");
			}
			a++;		
		}
	}
//	printf("after out\n");
	if (info->command_line[a] == '\0' && info->command_line[a - 1] != ' ')
	{
		fc_sub_str(info, a);
		info->nbr_sstr++;
//		printf("4 if out\n");
	}
}