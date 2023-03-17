/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   linklist_utils_02.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 16:31:38 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:33:05 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
void	remove_var(t_env **var_head, char *var_name)
{
	t_env	*ptr;
	t_env	*prev;

	prev = NULL;
	ptr = *var_head;
	while (ptr)
	{
		if (!ft_strncmp(var_name, ptr->name, ft_strlen(ptr->name) + 1))
		{
			if (prev)
				prev->next = ptr->next;
			else
				*var_head = ptr->next;
			ft_free_null(&ptr->name);
			ft_free_null(&ptr->data);
			ft_free_null((char **)&ptr);
			return ;
		}
		prev = ptr;
		ptr = ptr->next;
	}
}

/* ************************************************************************** */
int	size_var_list(t_env *var_head)
{
	int		i;
	t_env	*temp;

	temp = var_head;
	i = 0;
	while (temp != NULL)
	{
		temp = temp->next;
		i++;
	}
	return (i);
}

/* ************************************************************************** */
void	free_var_list(t_env **var_head)
{
	t_env	*tmp;
	t_env	*ptr;

	ptr = *var_head;
	while (ptr)
	{
		ft_free_null(&ptr->name);
		ft_free_null(&ptr->data);
		tmp = ptr->next;
		ft_free_null((char **)&ptr);
		ptr = tmp;
	}
	*var_head = NULL;
}

/* ************************************************************************** */
