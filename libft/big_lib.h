/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_lib.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/17 14:58:23 by ekern             #+#    #+#             */
/*   Updated: 2022/04/12 15:21:29 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIG_LIB_H
# define BIG_LIB_H

# include "libft_srcs/libft.h"

char	*get_next_line(int fd);
int		ft_printf(const char *src, ...);

#endif