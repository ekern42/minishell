/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:52:20 by angelo            #+#    #+#             */
/*   Updated: 2022/10/13 14:45:17 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	*fc_find_and_create_str(t_info *info)
{
	int		j;
	char	*str;

	while (info->envp)
	{
		while (info->envp->content != NULL)
		{
			if (ft_strncmp(info->envp->content, "PWD=", 5) == 0)
			{
				j = 3;
				str = malloc(sizeof(char) * ft_strlen(info->envp->content));
				if (!str)
					fc_error_exe(1, "malloc");
				while (str[j++] != '\0')
					return (str);
			}
			info->envp = info->envp->next;
		}
	}
	return ((int *)1);
}

int	fc_pwd(t_info *info, int i)
{
	(void)i;
	char	*str;

	str = fc_find_and_create_str(info);
	printf("str = %s\n", str);
	exit (0);
}

/*
int	fc_pwd(t_info *info, int i)
{
	int		j;
	char	*str;

	while (info->envp)
	{
		while (info->envp->content != NULL)
		{
			if (ft_strncmp(info->envp->content, "PWD=", 5) == 0)
			{
				j = 3;
				str = malloc(sizeof(char) * ft_strlen(info->envp->content));
				if (!str)
					fc_error_exe(1, "malloc");
				while (str[j++] != '\0')
					printf("%c", str[j]);
				printf("\n");
				return (0);
			}
			info->envp = info->envp->next;
		}
	}
	exit (0);
}
*/