/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:18:50 by jucarra           #+#    #+#             */
/*   Updated: 2026/03/31 19:59:18 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_power(int nb, int power);

int	ft_iterative_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 0)
	{
		nb = nb * nb;
		power--;
	}
	return (nb);
}

int	main(void)
{
	printf("5**0 = %d\n", ft_iterative_power(5, 0));
	printf("5**1 = %d\n", ft_iterative_power(5, 1));
	printf("5**2 = %d\n", ft_iterative_power(5, 2));
	printf("5**3 = %d\n", ft_iterative_power(5, 3));
	printf("5**4 = %d\n", ft_iterative_power(5, 4));
	return (0);
}
