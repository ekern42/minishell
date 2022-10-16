/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:18:19 by ekern             #+#    #+#             */
/*   Updated: 2022/10/16 17:05:01 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_malloc_dollar(t_info *info, int n)
{
	info->begin = malloc(sizeof(int) * (n + 1));
	info->end = malloc(sizeof(int) * (n + 1));
	if (!info->begin || !info->end)
		exit (0); // erreur a faire, malloc
	info->begin[n] = 0;
	info->end[n] = 0;
}


t_list	*fc_sub_dollar(t_list *sub_temp, t_info *info, char *str, int l)
{
	char	*str_temp;
	t_list	*list_temp;
	int	n;

	list_temp = sub_temp;
	str_temp = ft_substr(str, info->b_sub_str, l);
	ft_lstadd_back(&list_temp, ft_lstnew(str_temp));
	sub_temp = list_temp;
	return (sub_temp);
} 

static int	fc_strcmp_spec(char *s1, char *s2)
{
	int				a;
	int				b;
	unsigned char	val[2];

	if (s1[0] == '$')
		a = 0;
	else
		a = -1;
	b = -1;
	while (s1[++a] != '\0' && s2[++b] != '\0')
	{
		val[0] = s1[a];
		val[1] = s2[b];
		if (val[0] != val[1])
			return (val[0] - val[1]);
	}
	return (0);
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
		var_temp = info->var_list;
		if (ft_strncmp(sub_temp->content, "$?", 2) == 0)
		{
			/* A FAIRE */
			continue;
		}
		if (ft_strncmp(sub_temp->content, "$", 1) ==  0)
		{
			while (var_temp)
			{
//				printf("sub_temp %s var_temp %s\n", sub_temp->content, var_temp->name);
				if (fc_strcmp_spec(sub_temp->content, var_temp->name) == 0)
				{
					free (sub_temp->content);
					sub_temp->content = var_temp->content;
					break ;
				}
				var_temp = var_temp->next;
			}
			while (envp_temp)
			{
				if (fc_strcmp_spec(sub_temp->content, envp_temp->content) == 0)
				{
//					printf("sub_temp %s envp_temp %s\n", sub_temp->content, envp_temp->content);
					free (sub_temp->content);
					sub_temp->content = envp_temp->content;
					break ;
				}
//				printf("sub_temp %s envp_temp %s\n", sub_temp->content, envp_temp->content);
				envp_temp = envp_temp->next;
			}
		}
		sub_temp = sub_temp->next;
	}
	fc_dollar_fusion(info, sub);
}
