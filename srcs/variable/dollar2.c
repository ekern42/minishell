/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 11:39:51 by ekern             #+#    #+#             */
/*   Updated: 2022/10/17 11:45:07 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_dollar_fusion(t_info *info, t_list *sub)
{
	t_list	*sub_temp;
	t_list	*small_s_temp;
	int		a;
	char	*str;
	char	*str_temp;

	a = -1;
	sub_temp = sub;
	small_s_temp = info->small_str_list;
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
	while (++a < info->nbr_sstr && small_s_temp)
		small_s_temp = small_s_temp->next;
	free (small_s_temp->content);
	small_s_temp->content = str_temp;
}

static void	fc_replace_dollar2(t_list *sub, t_var *var, t_list *envp)
{
	char	*str;
	int		a;

	while (var)
	{
		if (fc_strcmp_spec(sub->content, var->name) == 0)
		{
			free (sub->content);
			sub->content = var->content;
			break ;
		}
		var = var->next;
	}
	while (envp)
	{
		if (fc_strcmp_spec(sub->content, envp->content) == 0)
		{
			a = ft_strlen(sub->content);
			str = ft_substr(envp->content, a, ft_strlen(envp->content) - a);
			free (sub->content);
			sub->content = str;
			break ;
		}
		envp = envp->next;
	}
}

void	fc_replace_dollar(t_info *info, t_list *sub)
{
	t_var	*var_temp;
	t_list	*sub_temp;
	t_list	*envp_temp;

	sub_temp = sub;
	envp_temp = info->envp;
	var_temp = info->var_list;
	while (sub_temp)
	{
		if (ft_strncmp(sub_temp->content, "$?", 2) == 0)
			printf("c'est pas fait\n"); // A FAIRE
		if (ft_strncmp(sub_temp->content, "$", 1) == 0)
			fc_replace_dollar2(sub_temp, var_temp, envp_temp);
		sub_temp = sub_temp->next;
	}
	fc_dollar_fusion(info, sub);
}
