/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   variable.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 12:41:00 by ekern             #+#    #+#             */
/*   Updated: 2022/10/14 13:26:39 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	fc_existant_var(t_info *info, char *str_name, char *str_content)
{
	t_var	*temp;

	if (!info->var_list)
		return (0);
	temp = info->var_list;
	while (temp)
	{
		if (ft_strncmp(str_name, temp->name, ft_strlen(str_name)) == 0)
		{
			free(temp->content);
			temp->content = str_content;
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

static void	fc_var_chain(t_info *info, char *str_name, char *str_content)
{
	t_var	*var_temp;
	t_var	*var_temp2;

	if (!fc_existant_var(info, str_name, str_content))
	{
		var_temp = malloc(sizeof(t_var));
		if (!var_temp)
			exit (0); // erreur a faire, malloc
		var_temp->name = str_name;
		var_temp->content = str_content;
		var_temp->next = NULL;
		if (!info->var_list)
			info->var_list = var_temp;
		else
		{
			var_temp2 = info->var_list;
			while (var_temp2->next != NULL)
				var_temp2 = var_temp2->next;
			var_temp2->next = var_temp;
		}
	}
}

static int	fc_variable_command(t_info *info, char *str, int a)
{
	int		b;
	char	*str_name;
	char	*str_content;

	if (a == 0)
		exit (0); // erreur a faire, command not found
	b = ft_strlen(str);
	str_name = malloc(sizeof(char) * (a + 1));
	str_content = malloc(sizeof(char) * (b - a));
	str_name[a] = '\0';
	str_content[b - a - 1] = '\0';
	b = -1;
	if (!ft_isalpha(str[0]))
		exit (0); // erreur a faire, command not found
	while (++b < a)
	{
		str_name[b] = str[b];
		if (!ft_isalnum(str[b]))
			exit (0); // erreur a faire, command not found
	}
	b = 0;
	while (str[++a] != '\0')
		str_content[b++] = str[a];
	fc_var_chain(info, str_name, str_content);
	return (1);
}

int	fc_check_variable(t_info *info)
{
	int		a;
	int		b;
	char	c;
	char	*str;

	a = -1;
	str = info->small_str_list->content;
	while (str[++a] != '\0')
	{
		if (str[a] == '\'' || str[a] == '\"')
		{
			b = a + 1;
			c = str[a];
			while (str[b] != c && str[b] != '\0')
				b++;
			if (str[b] != '\0')
				a = b;
		}
		if (str[a] == '=')
		{	
			fc_variable_command(info, str, a);
			return (1);
		}
	}
	return (0);
}
