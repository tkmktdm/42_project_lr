/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ultimate_div_mod.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 20:56:15 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/21 22:23:30 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_ultimate_div_mod(int *a, int *b);

void	ft_ultimate_div_mod(int *a, int *b)
{
	int	temp;

	temp = *a / *b;
	*b = *a % *b;
	*a = temp;
}

// int	main(void)
// {
// 	int	a;
// 	int	b;

// 	a = 13;
// 	b = 4;
// 	ft_ultimate_div_mod(&a, &b);
// 	printf("a: %d\n", a);
// 	printf("b: %d\n", b);
// 	return (0);
// }
