/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/30 13:09:39 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	do_convert(const char **fmt, va_list *ap)
{
	int	ret;

	if (**fmt != '%')
	{
		ret = write(1, *fmt, 1);
		(*fmt)++;
		return (ret);
	}
	(*fmt)++;
	if (!**fmt)
		return (0);
	ret = ft_handle_conversion(**fmt, ap);
	(*fmt)++;
	return (ret);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;
	int		ret;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		ret = do_convert(&format, &ap);
		if (ret == -1)
		{
			va_end(ap);
			return (-1);
		}
		count += ret;
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
