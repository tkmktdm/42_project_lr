/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 14:04:01 by htakumi           #+#    #+#             */
/*   Updated: 2026/05/30 12:54:07 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_putnbr_base(unsigned int n, char *base)
{
	unsigned int	len;

	len = ft_strlen(base);
	if (n >= len)
		if (ft_putnbr_base(n / len, base) == -1)
			return (-1);
	if (write(1, &base[n % len], 1) == -1)
		return (-1);
	return (1);
}
