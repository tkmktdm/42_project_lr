/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:08:35 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 08:31:41 by htakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_recursive_factorial(int nb)
{
	if (nb < 0)
		return (0);
	if (nb == 1 || nb == 0)
		return (1);
	return (nb * ft_recursive_factorial(nb - 1));
}

// int	main(void)
// {
// 	printf("3!: %d\n", ft_recursive_factorial(3));
// 	printf("-3!: %d\n", ft_recursive_factorial(-3));
// 	printf("5!: %d\n", ft_recursive_factorial(5));
// 	printf("12!: %d\n", ft_recursive_factorial(12));
// 	printf("13!: %d\n", ft_recursive_factorial(13));
// 	printf("0!: %d\n", ft_recursive_factorial(0));
// 	printf("1!: %d\n", ft_recursive_factorial(1));
// 	return (0);
// }
