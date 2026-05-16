/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:17:10 by htakumi           #+#    #+#             */
/*   Updated: 2026/05/16 13:31:44 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "../srcs/libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
int		ft_handle_conversion(char c, va_list *ap);
int		ft_print_char(va_list *ap);
int		ft_print_str(va_list *ap);
int		ft_print_int(va_list *ap);
int		ft_print_uint(va_list *ap);
int		ft_print_hex(va_list *ap, int upper);
int		ft_print_ptr(va_list *ap);
int		ft_print_percent(void);
void	ft_putnbr_base(unsigned int nbr, char *base);

#endif
