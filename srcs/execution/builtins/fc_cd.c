/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/06 12:51:19 by angelo            #+#    #+#             */
/*   Updated: 2022/10/01 19:01:49 by angelo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

//#include <string.h>
// size_t	ft_strlcat(char *dest, const char *src, size_t n)
/*
static void	list_files(t_info *info, const char *dirname)
{
	char			path[200];

	info->b->dir = opendir(dirname);
	if (info->b->dir == NULL)
		fc_error_tmp(1, "Problem with opendir\n");
	info->b->entity = readdir(info->b->dir);
	while (info->b->entity != NULL)
	{
		printf("%hhd %s / %s\n", info->b->entity->d_type, dirname, info->b->entity->d_name);
		if (info->b->entity->d_type == DT_DIR && ft_strncmp(info->b->entity->d_name, ".", 2) != 0 && ft_strncmp(info->b->entity->d_name, "..", 3) != 0)
		{
			ft_strjoin(path, dirname);
			ft_strjoin(path, "/");
			ft_strjoin(path, info->b->entity->d_name);
		}
		info->b->entity = readdir(info->b->dir);
		//printf("info->b->entity = %hhd\n", info->b->entity->d_type);
	}
	if (closedir(info->b->dir) < 0)
		fc_error_tmp(1, "Problem with closedir\n");
}
*/
int	fc_cd(t_info *info)
{
	//char	*path;
	(void)info;
	ft_putstr_fd("cd\nNot yet implemented\n", 1);

	//list_files(info, ".");
	//printf("----------------\n");
	//list_files(info, "..");
	//printf("----------------\n");
	//list_files(info, "./srcs");
	//info->idx = 1;
	//list_files(info, info->seg_command_line[info->idx]);

	// int chdir(const char *path);
	
	//path = "/home/angelo";
	//info->idx = 1;
//	if (strncmp(info->seg_command_line[1], ".", 2) == 0)
//	{
//		if (chdir("/home/angelo") < 0)
//			fc_error_tmp(1, "Problem with chdir\n");
//	}

/*
	char s[100];
  
	// printing current working directory
	printf("Avant : %s\n", getcwd(s, 100));
  
	// using the command
	
	if (strncmp(info->seg_command_line[1], ".", 2) == 0)
	{
		if (chdir(".") < 0)
			fc_error_tmp(1, "Problem with chdir\n");
	}

	if (strncmp(info->seg_command_line[1], "..", 3) == 0)
	{
		if (chdir("..") < 0)
			fc_error_tmp(1, "Problem with chdir\n");
	}
	
	// printing current working directory
	printf("Après : %s\n", getcwd(s, 100));
  
	// after chdir is executed
*/

	//if (info->b->entity->d_type == 4)
	//ft_putstr_fd("cd\nNot yet implemented\n", 1);
	return (0);
}
