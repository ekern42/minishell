/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:37 by ekern             #+#    #+#             */
/*   Updated: 2022/10/14 12:43:08 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	fc_dblstrlen(char **tab)
{
	int	a;

	a = -1;
	while (tab[++a] != NULL);
	return (a);
}

size_t	fc_strlen(const char *str)
{
	int	a;

	a = 0;
	while (str[a] != ' ' && str[a] != '\0')
		a++;
	return (a);
}

void	fc_test(char **envp)
{
	int	i;

	i = -1;
	while (envp[++i] != NULL)
		printf("{%d}%s{%d}\n", i, envp[i], i);
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

void fc_print_var_list(t_info *info)
{
	t_var	*temp;
	
	temp = info->var_list;
	while (temp)
	{
		printf("name %s, content %s\n", temp->name, temp->content);
		temp = temp->next;	
	}
}