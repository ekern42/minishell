/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_execve.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:31:17 by angelo            #+#    #+#             */
/*   Updated: 2022/10/04 19:54:38 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

	//// ls -la
	//printf("%s\n", info->exe->cmds[0][0]);
	//printf("%s\n", info->exe->cmds[0][1]);
	//// wc -l
	//printf("%s\n", info->exe->cmds[1][0]);
	//printf("%s\n", info->exe->cmds[1][1]);
	//// ls -la
	//printf("%s\n", info->exe->cmds[2][0]);
	//printf("%s\n", info->exe->cmds[2][1]);

static void	fc_print_tmp_str(char **str)
{
	int	i = 0;
	while (str[i] != NULL)
	{
		printf("str[i] = %s\n", str[i]);
		i++;
	}
	printf("str[i] = %s\n", str[i]);
}

static char **	fc_create_tmp_str(t_info *info)
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
	fc_print_tmp_str(str);
	return (str);
}



int	fc_execve_mlt_pipes(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_mlt_pipes(info, info->idx_re);
	//info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx_re][info->idx];
	info->exe->cmds_execve = fc_create_tmp_str(info);
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve\n");
	return (0);
}

int	fc_execve(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_for_execve(info);
	info->exe->cmds_execve = (char **)&info->exe->cmds[info->idx_re][info->idx];
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve\n");
	return (0);
}


int	fc_execve_redir(t_info *info)
{
	info->exe->path = NULL;
	info->exe->path = fc_path_for_execve(info);
	info->exe->cmds_execve = fc_create_left_str(info);
	if ((execve(info->exe->path, info->exe->cmds_execve, (char **)info->envp)) == -1)
		fc_error_tmp(1, "Problem with fc_execve_redir\n");
	return (0);
}
