/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalpha.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 15:48:58 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 16:18:50 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int	ft_isalpha(int c);

int	main(void)
{
	printf("'2': %d\n", ft_isalpha('2'));
	printf("'c': %d\n", ft_isalpha('c'));
	printf("'D': %d\n", ft_isalpha('D'));
	printf("'\\n': %d\n", ft_isalpha('\n'));
	printf("',': %d\n", ft_isalpha(','));
	printf("' ': %d\n", ft_isalpha(' '));
	// printf("' ': %d\n", ft_isalpha(" a"));
	printf("isalpha --------------------------\n");
	printf("'2': %d\n", isalpha('2'));
	printf("'c': %d\n", isalpha('c'));
	printf("'D': %d\n", isalpha('D'));
	printf("'\\n': %d\n", isalpha('\n'));
	printf("',': %d\n", isalpha(','));
	printf("' ': %d\n", isalpha(' '));
	// printf("' ': %d\n", isalpha(" a"));
	return (0);
}
