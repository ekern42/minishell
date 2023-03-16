/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 12:49:37 by ekern             #+#    #+#             */
/*   Updated: 2023/03/16 15:05:36 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	fc_dblstrlen(char **tab)
{
	int	a;

	a = -1;
	while (tab[++a] != NULL);
	return (a);
}

size_t	fc_strlen(const char *str, char c)
{
	int	a;

	a = 0;
	while (str[a] != c && str[a] != '\0')
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

void	fc_print_cmds(t_vars *info)
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

int	fc_valide_name(char *str)
{
	int	a;
	
	a = -1;
	if (!*str || !ft_isalpha(*str))
		return (0);
	while (str[++a])
	{
		if (!ft_isalnum(str[a]))
			return (0);
	}
	return (1);
}

char *fc_find_var(t_list *envp, char *name)
{
    while (envp != NULL)
    {
        char *var = envp->content;
        if (strncmp(var, name, strlen(name)) == 0 && var[strlen(name)] == '=')
        {
            return &var[strlen(name) + 1];
        }
        envp = envp->next;
    }
    return NULL;
}