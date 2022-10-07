/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_create_tmp_str.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/07 16:06:19 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 16:06:55 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fc_print_tmp_str(char **str)
{
	int	i = 0;
	while (str[i] != NULL)
	{
		printf("str[i] = %s\n", str[i]);
		i++;
	}
	printf("str[i] = %s\n", str[i]);
}

char **	fc_create_tmp_str(t_info *info)
{
	char	**str;
	int		i;
	
	i = 0;
	while (info->exe->cmds[info->idx_re][i])
		i++;
	//printf("i = %d\n", i);
	str = NULL;
	str = malloc(sizeof(char *) * i + 1);
	i = 0;
	while (info->exe->cmds[info->idx_re][i] != NULL)
	{
		str[i] = info->exe->cmds[info->idx_re][i];
		i++;
	}
	str[i] = NULL;
	//fc_print_tmp_str(str);
	return (str);
}
