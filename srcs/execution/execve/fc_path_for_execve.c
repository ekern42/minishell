/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_path_for_execve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:35:38 by angelo            #+#    #+#             */
/*   Updated: 2022/09/26 10:57:19 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		path = ft_strjoin(path_splited[i], info->seg_command_line[info->idx]);
		//printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			//printf("path = %s\n", path);
			return (path);
		}
		else if (access(path, X_OK) == -1)
			i++;
		else
			fc_error_tmp(1, "Problem access for path !\n");
	}
	return (NULL);
}

/*
void	*fc_path_for_execve(t_info *info)
{
	char	**path_splited;
	char	*path;
	int		i;

	path = NULL;
	path = fc_find_envp_without_name(info, "PATH");
	if (path == NULL)
		fc_error_tmp(1, "Problem with fc_find_envp_without_name !\n");
	path_splited = ft_split(path, ':');
	free (path);
	path = NULL;
	i = 0;
	while (path_splited[i] != NULL)
	{
		path_splited[i][ft_strlen(path_splited[i])] = '/';
		if (path_splited[0][ft_strlen(path_splited[0]) - 1] == '!')
			path_splited[0][ft_strlen(path_splited[0]) - 1] = '\0';
		//path = ft_strjoin(path_splited[i], info->seg_command_line[0]);
		//path = ft_strjoin(path_splited[i], *info->idx);
		path = ft_strjoin(path_splited[i], info->seg_command_line[info->idx]);
		//printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			//printf("path = %s\n", path);
			return (path);
		}
		else if (access(path, X_OK) == -1)
			i++;
		else
			fc_error_tmp(1, "Problem access for path !\n");
	}
	return (NULL);
}
*/

/*
void	*fc_path_for_execve(t_info *info)
{
	info->p->path = fc_find_envp_without_name(info, "PATH");
	if (info->p->path == NULL)
		fc_error_tmp(1, "Problem with fc_find_envp_without_name !\n");
	info->p->split = ft_split(info->p->path, ':');
	info->p->j = 0;
	while (info->seg_command_line[info->idx] != NULL)
	{
		info->p->i = 0;
		while (info->p->split[info->p->i] != NULL)
		{
			if (info->p->j == 0)
			{
				info->p->split[info->p->i][ft_strlen(info->p->split[info->p->i])] = '/';
				if (info->p->split[0][ft_strlen(info->p->split[0]) - 1] == '!')
					info->p->split[0][ft_strlen(info->p->split[0]) - 1] = '\0';
			}
			info->p->path = ft_strjoin(info->p->split[info->p->i], info->seg_command_line[info->idx]);
			if (access(info->p->path, X_OK) == 0)
			{
				//printf("info->p->path = %s\n", info->p->path);
				return (info->p->path);
			}
			else if (access(info->p->path, X_OK) == -1)
				info->p->i++;
			else
				fc_error_tmp(1, "Problem access for path !\n");
		}
		info->idx++;
		info->p->j++;
	}
	return (NULL);
}
*/
