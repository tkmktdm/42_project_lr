/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/16 13:31:29 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	ft_putptr_hex(unsigned long n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		ft_putptr_hex(n / 16);
	write(1, &base[n % 16], 1);
}

int	ft_print_ptr(va_list *ap)
{
	unsigned long	addr;
	unsigned long	tmp;
	int				len;

	addr = (unsigned long)va_arg(*ap, void *);
	if (!addr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	write(1, "0x", 2);
	ft_putptr_hex(addr);
	tmp = addr;
	len = 3;
	while (tmp >= 16)
	{
		tmp /= 16;
		len++;
	}
	return (len);
}
