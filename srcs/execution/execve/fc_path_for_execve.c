/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_path_for_execve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:35:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/16 14:33:36 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fc_path_for_execve(t_info *info, int index_re)
{
	char	**path_splited;
	char	*temp_path;
	char	*path;
	int		i;
	int		a;

	
	path = info->exe->cmds[index_re][0];
	if (access(path, X_OK) == 0)
		return (path);
	else
		path = fc_find_envp_path(info);
	if (path == NULL)
		fc_error_exe(1, "Problem with fc_find_envp_without_name !\n");
	path_splited = ft_split(path, ':');
	i = 0;
	while (path_splited[i] != NULL)
	{
		a = -1;
		temp_path = malloc(sizeof(char) * ft_strlen(path_splited[i] + 2));
		while (path_splited[i][++a] != '\0')
			temp_path[a] = path_splited[i][a];
		temp_path[a] = '/';
		temp_path[a + 1] = '\0';
		free(path_splited[i]);
		path_splited[i] = temp_path;
		path = ft_strjoin(path_splited[i], info->exe->cmds[index_re][0]);
		//printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			free(path_splited);
			//printf("path = %s\n", path);
			return (path);
		}
		else
		{
			free(path);
			path = NULL;
			i++;
		}
	}
	free (path);
	free (path_splited);
	return (NULL);
}

void	*fc_find_envp_path(t_info *info)
{
	t_list	*temp;
	char	*var;
	int		i;
	int		j;

	temp = info->envp;
	var = NULL;
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->content, "PATH=", 5) == 0)
		{
			var = temp->content;
			i = 0;
			j = 4;
			while (var[j++] != '\0')
				var[i++] = var[j];
			var[i - 1] = '\0';
			return (var);
		}
		temp = temp->next;
	}
	free(var);
	return (NULL);
}
