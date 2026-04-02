/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_power.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:21:47 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 10:56:02 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_recursive_power(int nb, int power)
{
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	if (power > 1)
	{
		return (nb * ft_recursive_power(nb, power - 1));
	}
	return (nb);
}

// int	main(void)
// {
// 	printf("5**0 = %d\n", ft_recursive_power(5, 0));
// 	printf("5**1 = %d\n", ft_recursive_power(5, 1));
// 	printf("5**2 = %d\n", ft_recursive_power(5, 2));
// 	printf("5**3 = %d\n", ft_recursive_power(5, 3));
// 	printf("5**4 = %d\n", ft_recursive_power(5, 4));
// 	return (0);
// }
