/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_path_for_execve.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aprosper <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:35:38 by angelo            #+#    #+#             */
/*   Updated: 2022/10/13 14:23:51 by aprosper         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fc_path_for_execve(t_info *info, int index_re)
{
	char	**path_splited;
	char	*path;
	int		i;

	path = fc_find_envp_without_name(info, "PATH");
	if (path == NULL)
		fc_error_exe(1, "Problem with fc_find_envp_without_name !\n");
	path_splited = ft_split(path, ':');
	i = 0;
	while (path_splited[i] != NULL)
	{
		path_splited[i][ft_strlen(path_splited[i])] = '/';
		if (path_splited[0][ft_strlen(path_splited[0]) - 1] == '!')
			path_splited[0][ft_strlen(path_splited[0]) - 1] = '\0';
		path = ft_strjoin(path_splited[i], info->exe->cmds[index_re][0]);
		//path = ft_strjoin(path_splited[i], info->exe->cmds[index_re][info->idx]);
		//printf("path = %s\n", path);
		if (access(path, X_OK) == 0)
		{
			printf("path = %s\n", path);
			return (path);
		}
		else
			i++;
	}
	return (NULL);
}

// without the name of $VAR
void	*fc_find_envp_without_name(t_info *info, char *var_env)
{
	t_list	*temp;
	char	*var;
	int		size;
	int		i;
	int		j;

	temp = info->envp;
	size = ft_strlen(var_env);
	while (temp->next != NULL)
	{
		if (ft_strncmp(temp->content, var_env, size) == 0)
		{
			var_env = temp->content;
			var = NULL;
			var = malloc(sizeof(char) * (ft_strlen(temp->content) - size));
			i = 0;
			j = size + 1;
			while (var_env[j] != '\0')
				var[i++] = var_env[j++];
			//printf("var = %s\n", var);
			return (var);
		}
		temp = temp->next;
		//printf("%s\n", (char *)temp->content);
	}
	return (NULL);
}
