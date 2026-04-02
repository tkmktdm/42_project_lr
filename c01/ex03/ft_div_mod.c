/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_div_mod.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/21 19:28:25 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/21 20:38:23 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

void	ft_div_mod(int a, int b, int *div, int *mod);

void	ft_div_mod(int a, int b, int *div, int *mod)
{
	int	dv;
	int	md;

	dv = a / b;
	md = a % b;
	*div = dv;
	*mod = md;
}

// int	main(void)
// {
// 	int	a;
// 	int	b;
// 	int	div;
// 	int	mod;

// 	a = 13;
// 	b = 3;
// 	ft_div_mod(a, b, &div, &mod);
// 	printf("a: %d\n", a);
// 	printf("b: %d\n", b);
// 	printf("div: %d\n", div);
// 	printf("mod: %d\n", mod);
// 	return (0);
// }
