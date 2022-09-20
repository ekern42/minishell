/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_path_for_execve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:35:38 by angelo            #+#    #+#             */
/*   Updated: 2022/09/19 19:28:14 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fc_path_for_execve(t_info *info)
{
	char	**path_splited;
	char	*path;
	int		i;

	path = NULL;
	path = fc_find_envp_without_name(info, "PATH"); // change PATH, ex LOL pour voir l'erreur
	if (path == NULL)
		printf("marche pas\n"); // à modifier qd je m'occuperai de la gestion d'erreurs
	path_splited = ft_split(path, ':');
	free (path);
	i = 0;
	while (path_splited[i] != NULL)
	{
		path_splited[i][ft_strlen(path_splited[i])] = '/';
		if (path_splited[0][ft_strlen(path_splited[0]) - 1] == '!')
			path_splited[0][ft_strlen(path_splited[0]) - 1] = '\0';
		//path = ft_strjoin(path_splited[i], info->seg_command_line[info->idx_seg_cmd_line]);
		path = ft_strjoin(path_splited[i], *info->seg_command_line);
		//printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			//printf("path = %s\n", path);
			return (path);
		}
		else if (access(path, X_OK) == -1)
			i++;
		else
			fc_error_exe2(3);
	}
	return (NULL);
}


/*
void	*fc_find_path_cmd(t_info *info)
{
	char	**path_splited;
	int		i;

	info->path = NULL;
	info->path = fc_find_envp_without_name(info, "PATH"); // change PATH, ex LOL pour voir l'erreur
	if (info->path == NULL)
		printf("marche pas\n"); // à modifier qd je m'occuperai de la gestion d'erreurs
	path_splited = ft_split(info->path, ':');
	//free (info->path);
	i = 0;
	while (path_splited[i] != NULL)
	{
		path_splited[i][ft_strlen(path_splited[i])] = '/';
		if (path_splited[0][ft_strlen(path_splited[0]) - 1] == '!')
			path_splited[0][ft_strlen(path_splited[0]) - 1] = '\0';
		info->path = ft_strjoin(path_splited[i], info->seg_command_line[0]);
		//info->path = ft_strjoin(path_splited[i], info->seg_command_line[info->idx_seg_cmd_line]);
		//printf("info->path = %s\n", info->path);
		if (access(info->path, X_OK) == 0)
		{
			printf("info->path = %s\n", info->path);
			return (info->path);
		}
		else if (access(info->path, X_OK) == -1)
			i++;
		else
			fc_error_exe2(100);
	}
	return (NULL);
}
*/