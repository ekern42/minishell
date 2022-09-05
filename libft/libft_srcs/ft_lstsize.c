/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstsize.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/05 14:53:44 by ekern             #+#    #+#             */
/*   Updated: 2022/09/05 16:51:02 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_lstsize(t_list *lst)
{
	int	i;

	i = 0;
	if (!lst)
		return (0);
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}
/*
int	main(void)
{
	t_list	*list;
	int		i;
	
	list = ft_lstnew("salut");
	ft_lstadd_front(&list, ft_lstnew("ca"));
	ft_lstadd_front(&list, ft_lstnew("va ?"));
	i = ft_lstsize(list);
	fc_print_chainlist(list, 's', 1);
	printf("Size of list : %d\n", i);
}
*/