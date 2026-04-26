/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isprint.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:22:22 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 17:31:22 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int	ft_isprint(int c);

int	main(void)
{
	printf("'2': %d\n", ft_isprint('2'));
	printf("'c': %d\n", ft_isprint('c'));
	printf("'D': %d\n", ft_isprint('D'));
	printf("'\\n': %d\n", ft_isprint('\n'));
	printf("',': %d\n", ft_isprint(','));
	printf("' ': %d\n", ft_isprint(' '));
	printf("'\\r': %d\n", ft_isprint('\r'));
	printf("'\\t': %d\n", ft_isprint('\t'));
	printf("'\\b': %d\n", ft_isprint('\b'));
	printf("isprint --------------------------\n");
	printf("'2': %d\n", isprint('2'));
	printf("'c': %d\n", isprint('c'));
	printf("'D': %d\n", isprint('D'));
	printf("'\\n': %d\n", isprint('\n'));
	printf("',': %d\n", isprint(','));
	printf("' ': %d\n", isprint(' '));
	printf("'\\r': %d\n", isprint('\r'));
	printf("'\\t': %d\n", isprint('\t'));
	printf("'\\b': %d\n", isprint('\b'));
	return (0);
}
