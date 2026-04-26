/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isalnum.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:41:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 17:03:42 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int	ft_isalnum(int c);

int	main(void)
{
	printf("'2': %d\n", ft_isalnum('2'));
	printf("'c': %d\n", ft_isalnum('c'));
	printf("'D': %d\n", ft_isalnum('D'));
	printf("'\\n': %d\n", ft_isalnum('\n'));
	printf("',': %d\n", ft_isalnum(','));
	printf("' ': %d\n", ft_isalnum(' '));
	// printf("' ': %d\n", ft_isalnum(" a"));
	printf("isalpha --------------------------\n");
	printf("'2': %d\n", isalnum('2'));
	printf("'c': %d\n", isalnum('c'));
	printf("'D': %d\n", isalnum('D'));
	printf("'\\n': %d\n", isalnum('\n'));
	printf("',': %d\n", isalnum(','));
	printf("' ': %d\n", isalnum(' '));
	// printf("' ': %d\n", isalnum(" a"));
	return (0);
}
