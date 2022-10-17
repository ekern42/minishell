/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/15 16:18:19 by ekern             #+#    #+#             */
/*   Updated: 2022/10/17 11:44:15 by ekern            ###   ########.fr       */
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
	int		n;

	list_temp = sub_temp;
	str_temp = ft_substr(str, info->b_sub_str, l);
	ft_lstadd_back(&list_temp, ft_lstnew(str_temp));
	sub_temp = list_temp;
	return (sub_temp);
}

int	fc_strcmp_spec(char *s1, char *s2)
{
	int				a;
	int				b;
	unsigned char	val[2];

	if (s1[0] == '$')
		a = 0;
	else
		a = -1;
	b = -1;
	while (s2[++b] != '=' && s2[b] != '\0')
	{
		a++;
		val[0] = s1[a];
		val[1] = s2[b];
		if (val[0] != val[1])
			return (val[0] - val[1]);
		if (s1[a] == '\0')
			return (0);
	}
	return (val[0] - val[1]);
}

void	fc_check_dollar(t_info *info)
{
	int		a;
	int		b;
	char	*str;
	t_list	*temp_lst;

	info->nbr_sstr = 0;
	temp_lst = info->small_str_list;
	while (temp_lst)
	{
		a = -1;
		b = 0;
		str = temp_lst->content;
		while (str[++a] != '\0')
		{
			if (str[a] == '$')
				b++;
		}
		if (b > 0)
			fc_dollar_details(info, str, b);
		info->nbr_sstr++;
		temp_lst = temp_lst->next;
	}
}
