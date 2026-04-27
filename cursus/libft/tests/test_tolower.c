/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_tolower.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:41:05 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/25 09:40:21 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int	ft_tolower(int c);

int	main(void)
{
	printf("'2': %c\n", ft_tolower('2'));
	printf("'c': %c\n", ft_tolower('c'));
	printf("'D': %c\n", ft_tolower('D'));
	printf("'\\n': %c\n", ft_tolower('\n'));
	printf("',': %c\n", ft_tolower(','));
	printf("' ': %c\n", ft_tolower(' '));
	printf("tolower --------------------------\n");
	printf("'2': %c\n", tolower('2'));
	printf("'c': %c\n", tolower('c'));
	printf("'D': %c\n", tolower('D'));
	printf("'\\n': %c\n", tolower('\n'));
	printf("',': %c\n", tolower(','));
	printf("' ': %c\n", tolower(' '));
	return (0);
}
