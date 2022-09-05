/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstlast.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:54:07 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 16:52:12 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_list		*ft_lstlast(t_list *lst)
{
	if (!lst)
		return (0);
	while (lst->next)
		lst = lst->next;
	return (lst);
}
/*
int	main(void)
{
	t_list	*list;
	t_list	*last;

	list = ft_lstnew("salut");
	ft_lstadd_front(&list, ft_lstnew("ca"));
	ft_lstadd_front(&list, ft_lstnew("va ?"));
	last = ft_lstlast(list);
	fc_print_chainlist(list, 's', 1);
	fc_print_chainlist(last, 's', 1);
}
*/