/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_path_for_execve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:35:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/04 10:36:36 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fc_path_mlt_pipes(t_info *info, int index)
{
	char	**path_splited;
	char	*path;
	int		i;

	path = fc_find_envp_without_name(info, "PATH");
	if (path == NULL)
		fc_error_tmp(1, "Problem with fc_find_envp_without_name !\n");
	path_splited = ft_split(path, ':');
	i = 0;
	while (path_splited[i] != NULL)
	{
		path_splited[i][ft_strlen(path_splited[i])] = '/';
		if (path_splited[0][ft_strlen(path_splited[0]) - 1] == '!')
			path_splited[0][ft_strlen(path_splited[0]) - 1] = '\0';
		path = ft_strjoin(path_splited[i], info->exe->cmds[index][0]);
		//printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			//printf("path = %s\n", path);
			return (path);
		}
		else
			i++;
	}
	return (NULL);
}

void	*fc_path_for_execve(t_info *info)
{
	char	**path_splited;
	char	*path;
	int		i;

	path = fc_find_envp_without_name(info, "PATH");
	if (path == NULL)
		fc_error_tmp(1, "Problem with fc_find_envp_without_name !\n");
	path_splited = ft_split(path, ':');
	i = 0;
	while (path_splited[i] != NULL)
	{
		path_splited[i][ft_strlen(path_splited[i])] = '/';
		if (path_splited[0][ft_strlen(path_splited[0]) - 1] == '!')
			path_splited[0][ft_strlen(path_splited[0]) - 1] = '\0';
		path = ft_strjoin(path_splited[i], info->exe->cmds[info->idx2][info->idx]);
		//printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			//printf("path = %s\n", path);
			return (path);
		}
		else
			i++;
	}
	return (NULL);
}
