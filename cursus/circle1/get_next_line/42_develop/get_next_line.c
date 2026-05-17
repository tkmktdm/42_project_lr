/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/18 07:54:52 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%')
		{
			format++;
			count += ft_handle_conversion(*format, &ap);
		}
		else
			count += write(1, format, 1);
		format++;
	}
	va_end(ap);
	return (count);
}

int	ft_handle_conversion(char c, va_list *ap)
{
	if (c == 'c')
		return (ft_print_char(ap));
	else if (c == 's')
		return (ft_print_str(ap));
	else if (c == 'p')
		return (ft_print_ptr(ap));
	else if (c == 'd' || c == 'i')
		return (ft_print_int(ap));
	else if (c == 'u')
		return (ft_print_uint(ap));
	else if (c == 'x')
		return (ft_print_hex(ap, 0));
	else if (c == 'X')
		return (ft_print_hex(ap, 1));
	else if (c == '%')
		return (ft_print_percent());
	return (0);
}
