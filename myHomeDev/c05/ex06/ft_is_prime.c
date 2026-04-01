/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_prime.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:38:56 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 10:44:33 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_is_prime(int nb)
{
	int	i;

	i = 2;
	if (nb < 2)
		return (0);
	if (nb == 2)
		return (1);
	while (i * i <= nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

// int	main(void)
// {
// 	printf("ft_sqrt: %d\n", ft_is_prime(15));
// 	printf("ft_sqrt: %d\n", ft_is_prime(11));
// 	printf("ft_sqrt: %d\n", ft_is_prime(0));
// 	printf("ft_sqrt: %d\n", ft_is_prime(-1));
// 	printf("ft_sqrt: %d\n", ft_is_prime(1));
// 	printf("ft_sqrt: %d\n", ft_is_prime(2));
// 	printf("ft_sqrt: %d\n", ft_is_prime(71));
// 	return (0);
// }
