/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/26 16:17:10 by htakumi           #+#    #+#             */
/*   Updated: 2026/05/23 18:08:12 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "libft/libft.h"
# include <stdarg.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_printf(const char *format, ...)__attribute__((format(printf, 1, 2)));
int		ft_handle_conversion(char c, va_list *ap);
int		ft_print_char(va_list *ap);
int		ft_print_str(va_list *ap);
int		ft_print_int(va_list *ap);
int		ft_print_uint(va_list *ap);
int		ft_print_hex(va_list *ap, int upper);
int		ft_print_ptr(va_list *ap);
int		ft_print_percent(void);
void	ft_putnbr_base(unsigned int nbr, char *base);
void	ft_putptr_hex(unsigned long n);

#endif
