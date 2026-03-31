/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:18:50 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 08:32:12 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_iterative_power(int nb, int power);

int	ft_iterative_power(int nb, int power)
{
	int base;
	base = nb;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 1)
	{
		nb = nb * base;
		power--;
	}
	return (nb);
}

// int	main(void)
// {
// 	printf("5**0 = %d\n", ft_iterative_power(5, 0));
// 	printf("5**1 = %d\n", ft_iterative_power(5, 1));
// 	printf("5**2 = %d\n", ft_iterative_power(5, 2));
// 	printf("5**3 = %d\n", ft_iterative_power(5, 3));
// 	printf("5**4 = %d\n", ft_iterative_power(5, 4));
// 	return (0);
// }
