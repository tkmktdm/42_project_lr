/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/30 12:54:00 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putptr_hex(unsigned long n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		if (ft_putptr_hex(n / 16) == -1)
			return (-1);
	if (write(1, &base[n % 16], 1) == -1)
		return (-1);
	return (1);
}

int	ft_print_ptr(va_list *ap)
{
	unsigned long	addr;
	unsigned long	tmp;
	int				len;

	addr = (unsigned long)va_arg(*ap, void *);
	if (!addr)
	{
		if (write(1, "(nil)", 5) == -1)
			return (-1);
		return (5);
	}
	if (write(1, "0x", 2) == -1)
		return (-1);
	if (ft_putptr_hex(addr) == -1)
		return (-1);
	tmp = addr;
	len = 3;
	while (tmp >= 16)
	{
		tmp /= 16;
		len++;
	}
	return (len);
}
