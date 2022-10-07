/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:16:47 by angelo            #+#    #+#             */
/*   Updated: 2022/10/07 12:42:19 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

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

void	fc_print_cmds(t_info *info)
{
	int	i;
	int	j;
	int	size;
	
	size = 0;
	while (info->exe->cmds[size])
		size++;
	printf("info->exe->cmds[i][j] : \n");
	i = 0;
	while (i < size)
	{
		j = 0;
		while (info->exe->cmds[i][j] != NULL)
		{
			printf("%s\n", info->exe->cmds[i][j]);
			j++;
		}
		i++;
	}
	printf("----------\n");
}

int	fc_find_idx_file(t_info *info, char *re, int size)
{
	info->idx = 0;
	while (info->exe->cmds[info->idx_re][info->idx++] != NULL)
	{
		if (strncmp(info->exe->cmds[info->idx_re][info->idx], re, size) == 0)
		{
			info->idx++;
			break ;
		}
	}
	return (info->idx);
}
