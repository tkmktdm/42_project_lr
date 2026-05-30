/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/30 15:00:10 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_hex(va_list *ap, int upper)
{
	unsigned int	u;
	int				len;
	char			*base;

	u = va_arg(*ap, unsigned int);
	if (upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (ft_putnbr_base(u, base) == -1)
		return (-1);
	len = 1;
	while (u >= 16)
	{
		u /= 16;
		len++;
	}
	return (len);
}
