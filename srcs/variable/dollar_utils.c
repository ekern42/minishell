/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:18:19 by ekern             #+#    #+#             */
/*   Updated: 2022/10/15 17:09:35 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_list	*fc_sub_str(t_list *sub_temp, char *str, int *begin, int *end)
{
	
}

/*
void	fc_replace_dollar(t_var *temp_var, char *small_str)
{
	t_var	*temp_var;

	temp_var = info->var_list;
	while (temp_var)
	{
		if (ft_strncmp(small_str, temp_var->name, ft_strlen(small_str)) == 0)
		{
			free(small_str);
			small_str = temp_var->content;
		}
		temp_var = temp_var->next;
	}
}
*/