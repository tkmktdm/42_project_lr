/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_sqrt.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:28:23 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 10:18:44 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_sqrt(int nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		return (0);
	}
	if (nb == 1)
	{
		return (1);
	}
	while (i <= nb / 2 && i <= 46341)
	{
		if (i * i == nb)
		{
			return (i);
		}
		i++;
	}
	return (0);
}

// int	main(void)
// {
// 	printf("ft_sqrt: %d\n", ft_sqrt(25));
// 	printf("ft_sqrt: %d\n", ft_sqrt(0));
// 	printf("ft_sqrt: %d\n", ft_sqrt(-1));
// 	printf("ft_sqrt: %d\n", ft_sqrt(1));
// 	printf("ft_sqrt: %d\n", ft_sqrt(81));
// 	return (0);
// }
