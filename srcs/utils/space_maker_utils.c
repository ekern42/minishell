/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   space_maker_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/24 11:40:25 by ekern             #+#    #+#             */
/*   Updated: 2023/03/17 12:33:55 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* ************************************************************************** */
char	*insert_space_before_actual_pos(char *line, int *actual_position)
{
	char	*start;
	char	*start_with_space;
	char	*end;
	int		qty;

	qty = *actual_position;
	start = ft_substr(line, 0, qty);
	qty = ft_strlen(line) - *actual_position;
	end = ft_substr(line, *actual_position, qty);
	start_with_space = ft_strjoin(start, " ");
	free(start);
	free(line);
	line = ft_strjoin(start_with_space, end);
	free(start_with_space);
	free(end);
	(*actual_position)++;
	return (line);
}

/* ************************************************************************** */
char	*insert_space_after_actual_pos(char *line, int *actual_position)
{
	char	*start;
	char	*start_with_space;
	char	*end;
	int		qty;

	qty = *actual_position + 1;
	start = ft_substr(line, 0, qty);
	qty = ft_strlen(line) - *actual_position;
	end = ft_substr(line, *actual_position + 1, qty);
	start_with_space = ft_strjoin(start, " ");
	free(start);
	free(line);
	line = ft_strjoin(start_with_space, end);
	free(start_with_space);
	free(end);
	return (line);
}

/* ************************************************************************** */