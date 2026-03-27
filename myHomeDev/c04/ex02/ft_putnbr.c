/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/27 09:44:20 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 10:13:33 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int nb);

void	ft_putnbr(int nb)
{
	char	n;

	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb / 10 != 0)
	{
		ft_putnbr(nb / 10);
	}
	n = nb % 10 + '0';
	write(1, &n, 1);
}

int	main(void)
{
	ft_putnbr(420000);
	write(1, "\n", 1);
	ft_putnbr(-42);
	write(1, "\n", 1);
	ft_putnbr(__INT_MAX__);
	write(1, "\n", 1);
	ft_putnbr(-__INT_MAX__);
	write(1, "\n", 1);
	ft_putnbr(4.2);
	// write(1, "\n", 1);
	// ft_putnbr(11);
	// write(1, "\n", 1);
	// ft_putnbr(3);
	// write(1, "\n", 1);
	// ft_putnbr(0);
	// write(1, "\n", 1);
	// ft_putnbr(199);
	// write(1, "\n", 1);
	// ft_putnbr(1);
	return (0);
}
