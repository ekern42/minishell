/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 16:53:02 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 17:01:29 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	if (*lst == 0)
		*lst = new;
	else
		(ft_lstlast(*lst))->next = new;
}
/*
int	main(void)
{
	t_list	*list;

	list = ft_lstnew("salut");
	ft_lstadd_front(&list, ft_lstnew("ca"));
	ft_lstadd_front(&list, ft_lstnew("va ?"));
	ft_lstadd_back(&list, ft_lstnew("ouech"));
	fc_print_chainlist(list, 's', 1);
}
*/