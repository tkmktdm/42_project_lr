/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/16 12:56:11 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uint(va_list *ap)
{
	unsigned int	u;
	int				len;

	u = va_arg(*ap, unsigned int);
	ft_putnbr_base(u, "0123456789");
	len = 1;
	while (u >= 10)
	{
		u /= 10;
		len++;
	}
	return (len);
}
