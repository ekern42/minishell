/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:52:20 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 19:01:43 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fc_pwd(t_info *info)
{
	int		i;
	char	*new_pwd_str;

	while (info->envp)
	{
		while (info->envp->content != NULL)
		{
			if (ft_strncmp(info->envp->content, "PWD=", 4) == 0)
			{
				i = 3;
				new_pwd_str = info->envp->content;
				while (new_pwd_str[i++] != '\0')
					printf("%c", new_pwd_str[i]);
				printf("\n");
				return (0);
			}
			info->envp = info->envp->next;
		}
	}
	exit (0);
	//return (1);
}
