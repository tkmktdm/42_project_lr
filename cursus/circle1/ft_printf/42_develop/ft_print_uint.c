/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_uint.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/30 12:54:01 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_uint(va_list *ap)
{
	unsigned int	u;
	int				len;

	u = va_arg(*ap, unsigned int);
	if (ft_putnbr_base(u, "0123456789") == -1)
		return (-1);
	len = 1;
	while (u >= 10)
	{
		u /= 10;
		len++;
	}
	return (len);
}
