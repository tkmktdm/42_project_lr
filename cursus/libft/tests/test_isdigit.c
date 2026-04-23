/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isdigit.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:19:45 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 16:35:58 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

int	ft_isdigit(int i);

int	main(void)
{
	printf("'2': %d\n", ft_isdigit('2'));
	printf("'c': %d\n", ft_isdigit('c'));
	printf("'D': %d\n", ft_isdigit('D'));
	printf("'\\n': %d\n", ft_isdigit('\n'));
	printf("',': %d\n", ft_isdigit(','));
	printf("' ': %d\n", ft_isdigit(' '));
	printf(" --------------------------\n");
	printf("'2': %d\n", isdigit('2'));
	printf("'c': %d\n", isdigit('c'));
	printf("'D': %d\n", isdigit('D'));
	printf("'\\n': %d\n", isdigit('\n'));
	printf("',': %d\n", isdigit(','));
	printf("' ': %d\n", isdigit(' '));
	return (0);
}
