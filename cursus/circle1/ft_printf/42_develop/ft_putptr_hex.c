/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr_hex.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:04:01 by htakumi           #+#    #+#             */
/*   Updated: 2026/05/16 14:01:23 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putptr_hex(unsigned long n)
{
	char	*base;

	base = "0123456789abcdef";
	if (n >= 16)
		ft_putptr_hex(n / 16);
	write(1, &base[n % 16], 1);
}
