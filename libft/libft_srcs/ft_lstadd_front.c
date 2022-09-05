/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_front.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:53:19 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 16:57:21 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_front(t_list **lst, t_list *new)
{
	new->next = *lst;
	*lst = new;
}
/*
int	main(void)
{
	t_list	*list;

	list = ft_lstnew("salut");
	ft_lstadd_front(&list, ft_lstnew((void*)42));
	printf("1er maillon : %d et 2eme maillon : %s\n", list->content, list->next->content);
}
*/