/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:52:20 by angelo            #+#    #+#             */
/*   Updated: 2022/10/13 19:02:03 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	*fc_find_and_create_str(t_info *info)
{
	int		i;
	int		j;
	char	*str;
	t_list	*temp;

	temp = info->envp;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->content, "PWD=", 4) == 0)
		{
			str = temp->content;
			i = 0;
			j = 3;
			while (str[j++] != '\0')
				str[i++] = str[j];
			str[i - 1] = '\n';
			str[i] = '\0';
			return (str);
		}
		temp = temp->next;
	}
	return (NULL);
}

int	fc_pwd(t_info *info, int i)
{
	if (i < info->lex->nbr_pipe)
		info->b->local_fd = info->exe->fd[1];
	else
		info->b->local_fd = 1; // last command = stdout
	ft_putstr_fd(fc_find_and_create_str(info), info->b->local_fd);
	exit (0);
}
