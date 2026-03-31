/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterative_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:00:50 by jucarra           #+#    #+#             */
/*   Updated: 2026/03/31 08:40:52 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

int	ft_iterative_factorial(int nb)
{
	int i;

	i = nb;
	if (nb < 0 || nb > 12) {
		return 0;
	} else if (nb == 0 || nb == 1) {
		return (1);
	}
	while (i > 1)
	{
		nb = nb * (i - 1);
		i--;
	}
	return nb;
}

// int main () {
// 	printf("3!: %d\n", ft_iterative_factorial(3));
// 	printf("-3!: %d\n", ft_iterative_factorial(-3));
// 	printf("1!: %d\n", ft_iterative_factorial(1));
// 	printf("12!: %d\n", ft_iterative_factorial(12));
// 	printf("13!: %d\n", ft_iterative_factorial(13));
// 	printf("-4!: %d\n", ft_iterative_factorial(-4));
// 	printf("0!: %d\n", ft_iterative_factorial(0));
// 	return 0;
// }
