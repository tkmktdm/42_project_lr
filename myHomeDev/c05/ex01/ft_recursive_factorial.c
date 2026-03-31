/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:08:35 by jucarra           #+#    #+#             */
/*   Updated: 2026/03/31 08:14:16 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_factorial(int nb)
{
	if (nb > 2147483647 || nb < -2147483648) {
		return 0;
	}
		printf("3!: %d\n", nb);

	int nagative;
	nagative = 1;
	if (nb < 0) {
		nagative = -1;
		nb = -nb;
	}
	if (nb != 1) {
		nb = nb * ft_iterative_factorial(nb-1);
	}
	

	return nb * nagative;
}

int main () {
	printf("3!: %d\n", ft_iterative_factorial(3));
	printf("3!: %d\n", ft_iterative_factorial(-3));
	printf("5!: %d\n", ft_iterative_factorial(5));
	printf("5!: %d\n", ft_iterative_factorial(2147483647));
	// printf("5!: %d\n", ft_iterative_factorial(2147483648));
	printf("5!: %d\n", ft_iterative_factorial(-2147483648));
	// printf("5!: %d\n", ft_iterative_factorial(-2147483648));

	return 0;
}

// int	ft_recursive_factorial(int nb)
// {
// 	if (nb < 0)
// 		return (0);
// 	if (nb == 0 || nb == 1)
// 		return (1);
// 	return (nb * ft_recursive_factorial(nb - 1));
// }
