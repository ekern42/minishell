/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_re_del.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/12 11:18:29 by ekern             #+#    #+#             */
/*   Updated: 2022/10/12 13:29:58 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_list *fc_addin_list(t_list *lst, char *line)
{
	t_list	*new;

	new = lst;
	ft_lstadd_back(&new, ft_lstnew((void *)line));
	return (new);
}

int	fc_putlist(t_list *lst)
{
	t_list *temp;
	
	temp = lst;
	while (temp)
	{
		ft_putstr_fd((char *)temp->content, 1);
		temp = temp->next;
	}
//	ft_putchar_fd('\n', 1);
	return(0);
}
int	fc_re_del(t_info *info, int a, int i)
{
	char	*line;
	t_list	*lst;

	if (ft_strncmp(info->exe->cmds[i][a], "<<", 3) == 0)
	{
		lst = NULL;
		while (1)
		{
			ft_putstr_fd("> ", 1);
			line = get_next_line(0);
			if (!line)
				return (2);
			if (ft_strncmp(line, "temp", 4) == 0)
				break;
			lst = fc_addin_list(lst, line);
		}
		free(line);
		
		fc_putlist(lst);
		return (1);
	}
	return (0);
}