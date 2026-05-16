/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/16 12:57:24 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int	ft_print_hex(va_list *ap, int upper)
{
	unsigned int	u;
	int				len;

	u = va_arg(*ap, unsigned int);
	if (upper)
		ft_putnbr_base(u, "0123456789ABCDEF");
	else
		ft_putnbr_base(u, "0123456789abcdef");
	len = 1;
	while (u >= 16)
	{
		u /= 16;
		len++;
	}
	return (len);
}
