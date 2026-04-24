/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokubo <kokubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:15:00 by kokubo            #+#    #+#             */
/*   Updated: 2026/04/23 01:00:00 by kokubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	put_uint(unsigned int n, int fd)
{
	if (n >= 10)
		put_uint(n / 10, fd);
	ft_putchar_fd((char)('0' + (n % 10)), fd);
}

void	ft_putnbr_fd(int n, int fd)
{
	unsigned int	u;

	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		u = -(unsigned int)n;
	}
	else
	{
		u = (unsigned int)n;
	}
	put_uint(u, fd);
}
