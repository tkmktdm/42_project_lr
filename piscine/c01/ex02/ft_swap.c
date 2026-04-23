/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_swap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 18:30:10 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/21 19:27:40 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_swap(int *a, int *b);

void	ft_swap(int *a, int *b)
{
	int	temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

// int	main(void)
// {
// 	int	a;
// 	int	b;

// 	a = 19;
// 	b = 42;
// 	printf("a: %d\n", a);
// 	printf("b: %d\n", b);
// 	printf("swap \n");
// 	ft_swap(&a, &b);
// 	printf("a: %d\n", a);
// 	printf("b: %d\n", b);
// 	return (0);
// }
