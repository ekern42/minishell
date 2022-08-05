/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ekern <ekern@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/26 12:02:03 by ekern             #+#    #+#             */
/*   Updated: 2022/03/14 13:44:52 by ekern            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>
# include <stdio.h>
# include <limits.h>

/* Principal part */

int		ft_printf(const char *src, ...);
int		fc_check(const char c, va_list param);

/* Utility part */

void	fc_putchar_printf(const char c);
void	fc_putnbr_printf(unsigned int n);
int		fc_strlen_printf(const char *str);

/* Final part */

int		fc_char(va_list param);
int		fc_string(va_list param);
int		fc_decim(va_list param);
int		fc_int(va_list param);
int		fc_unsint(va_list param);
int		fc_perc(va_list param);
int		fc_pointer(va_list param);
int		fc_hexa(va_list param, int n);

#endif