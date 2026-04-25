/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_toupper.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:41:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/25 09:39:49 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int	ft_toupper(int c);

int	main(void)
{
	printf("'2': %c\n", ft_toupper('2'));
	printf("'c': %c\n", ft_toupper('c'));
	printf("'D': %c\n", ft_toupper('D'));
	printf("'\\n': %c\n", ft_toupper('\n'));
	printf("',': %c\n", ft_toupper(','));
	printf("' ': %c\n", ft_toupper(' '));
	printf("toupper --------------------------\n");
	printf("'2': %c\n", toupper('2'));
	printf("'c': %c\n", toupper('c'));
	printf("'D': %c\n", toupper('D'));
	printf("'\\n': %c\n", toupper('\n'));
	printf("',': %c\n", toupper(','));
	printf("' ': %c\n", toupper(' '));
	return (0);
}
