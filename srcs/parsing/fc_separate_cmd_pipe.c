/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fc_separate_cmd_pipe.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/18 19:48:43 by angelo            #+#    #+#             */
/*   Updated: 2022/09/20 12:32:20 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_go_until_pipe(t_info *info)
{
	int	i;
	
	i = 0;
	while (info->seg_command_line[i] != NULL)
	{
		if (ft_strncmp(info->seg_command_line[i], "|", 2) == 0)
			return (i);
		i++;
	}
	return (i);
}

int	fc_go_until_next(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	while (info->seg_command_line[i] != NULL)
	{
		if (ft_strncmp(info->seg_command_line[i], "|", 2) == 0)
			break ;
		i++;
	}
	j = info->exe->size_seg_cmd_line - 1; // 1 pour le pipe
	j = j - i;
	return (j);
}

char	**fc_cpy_cmd2(t_info *info)
{
	int		i;
	int		j;
	char	**tab;
	

	j = fc_go_until_next(info) + 1;
	//printf("j = %d\n", j);
	tab = malloc(sizeof(char *) * j + 1);
	i = 0;
	while (info->seg_command_line[j] != NULL)
	{
		tab[i] = info->seg_command_line[j];
		i++;
		j++;
	}
	tab[i] = NULL;
	//printf("------------------\n");
	printf("tab(fc_cpy_cmd2) = \n");
	printf("%s\n%s\n%s\n", tab[0], tab[1], tab[2]);
	printf("------------------\n");
	return (tab);
}

char	**fc_cpy_cmd(t_info *info)
{
	int		i;
	int		j;
	char	**tab;
	
	i = 0;
	while (info->seg_command_line[i] != NULL)
	{
		if (ft_strncmp(info->seg_command_line[i], "|", 2) == 0)
			break ;
		i++;
	}
	tab = malloc(sizeof(char *) * i + 1);
	j = 0;
	while (j < i)
	{
		tab[j] = info->seg_command_line[j];
		j++;
	}
	tab[j] = NULL;
	//printf("------------------\n");
	printf("tab(fc_cpy_cmd) = \n");
	printf("%s\n%s\n%s\n", tab[0], tab[1], tab[2]);
	printf("------------------\n");
	return (tab);
}


/*
char	**fc_copy_pipe_cmd(char **cmd_line)
{
	int		i;
	char	**lst;

	i = 0;
	while (cmd_line[1] != NULL)
	{
		if (ft_strncmp(cmd_line[i], "|", 2) == 0)
			break ;
		i++;
	}
	lst = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (cmd_line[i] != NULL)
	{
		if (ft_strncmp(cmd_line[i], "|", 2) == 0)
			break ;
		lst[i] = cmd_line[i];
		i++;
	}
	lst[i] = NULL;
	return (lst);
}

int	fc_separate_cmd_pipe(t_info *info)
{
	char	**tmp_cmd_line;
	int		i;

	i = 0;
	tmp_cmd_line = info->seg_command_line;
	info->exe->cmds = malloc(sizeof(char **) * (info->exe->nbr_pipe + 2));
	while (i < info->exe->nbr_pipe + 1)
	{
		info->exe->cmds[i] = fc_copy_pipe_cmd(tmp_cmd_line);
		while (tmp_cmd_line[0] != NULL) // skip jusqu'au pipe
		{
			if (ft_strncmp(tmp_cmd_line[0], "|", 2) == 0)
			{
				tmp_cmd_line++;
				break ;
			}
			tmp_cmd_line++;
		}
		i++;
	}
	info->exe->cmds[info->exe->nbr_pipe + 1] = NULL;
	//printf("%s %s\n %s %s\n", info->exe->cmds[0][0], info->exe->cmds[0][1], info->exe->cmds[1][0], info->exe->cmds[1][1]);
	return (1);
}
*/