/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fibonacci.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/15 10:24:36 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/01 10:56:28 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_fibonacci(int index)
{
	if (index < 0)
	{
		return (-1);
	}
	else if (index == 0)
	{
		return (0);
	}
	else if (index == 1)
	{
		return (1);
	}
	else
	{
		return (ft_fibonacci(index - 2) + ft_fibonacci(index - 1));
	}
	return (0);
}

// int	main(void)
// {
// 	printf("0: %d\n", ft_fibonacci(0));
// 	printf("-1: %d\n", ft_fibonacci(-1));
// 	printf("3: %d\n", ft_fibonacci(3));
// 	printf("12: %d\n", ft_fibonacci(12));
// 	return (0);
// }
