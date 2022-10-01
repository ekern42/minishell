/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_exe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: angelo <marvin@42lausanne.ch>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/12 13:16:47 by angelo            #+#    #+#             */
/*   Updated: 2022/10/01 14:26:48 by angelo           ###   ########.fr       */
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

/*
// Emmanuel version :
void	*fc_find_envp_without_name(t_info *info, char *var_env)
{
	t_list	*temp;	// ultra necessaire
	int		size;
	int		i;
	int		j;
	char	*var;

	temp = info->envp;
	size = ft_strlen(var_env);
	// J'ai virer la boucle while (temp != NULL) c'est elle qui foutait la M (elle servait a rien)
	while (temp->next != NULL) // temp->content changer en temp->next, temp->next est toujours NULL des que tu atteint la fin de la liste chainee, pas le cas de temp->content (donnee aleatoire de la memoir)
	{
			if (ft_strncmp(temp->content, var_env, size) == 0)
			{
				var_env = temp->content;
				var = malloc(sizeof(char) * (ft_strlen(temp->content) - size));
				//var = var_env; PLUS JAMAIS CETTE ERREUR PLEASE
				i = 0;
				j = size + 1;
				while (var[i] != '\0')
					var[i++] = var_env[j++];
				return (var);
			}
			temp = temp->next;
//			printf("%s\n", (char *)temp->content); // pour voir le contenu ligne par ligne de la liste temp
	}
	return (NULL); // j'ai changer le return d'erreur, c'est plus logique avec un NULL
}
*/

void	*fc_find_envp_with_name(t_info *info, char *var_env)
{
	int		size;
	//char	*new_pwd;

	size = ft_strlen(var_env);
	while (info->envp != NULL)
	{
		while (info->envp->content != NULL)
		{
			if (ft_strncmp(info->envp->content, var_env, size) == 0)
			{
				//new_pwd = malloc(sizeof(char) * 1000);
				//new_pwd = "PWD=/home/angelo/Projets/minishell/srcs";
				info->envp->content = NULL;
				info->envp->content = "PWD=/home/angelo/Projets/minishell/srcs";
				//info->envp->content = new_pwd;
				printf("%s\n", (char *)info->envp->content);
				return (info->envp->content);
			}
			info->envp = info->envp->next;
		}
	}
	return (NULL);
}

/*
// with the name of $VAR
void	*fc_find_envp_with_name(t_info *info, char *var_env)
{
	int		size;

	size = ft_strlen(var_env);
	while (info->envp != NULL)
	{
		while (info->envp->content != NULL)
		{
			if (ft_strncmp(info->envp->content, var_env, size) == 0)
			{
				//printf("%s\n", (char *)info->envp->content);
				return (info->envp->content);
			}
			else
				info->envp = info->envp->next;
		}
	}
	return (NULL);
}
*/
/*
void	fc_print_seg_cmd_line(t_info *info)
{
	int	i;

	i = 0;
	//printf("info->seg_command_line[i] :\n");
	while (info->seg_command_line[i] != NULL)
	{
		printf("%s\n", (char *)info->seg_command_line[i]);
		i++;
	}
}
void	fc_print_seg_cmd_line2(t_info *info)
{

	info->idx = 0;
	while (info->seg_command_line[info->idx] != NULL)
	{
		printf("info->seg_command_line[idx] = %s | idx = %d\n", (char *)info->seg_command_line[info->idx], info->idx);
		info->idx++;
	}
	info->idx = 0;
}
*/
