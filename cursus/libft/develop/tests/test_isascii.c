/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_isascii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 16:55:54 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 17:21:20 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <ctype.h>
#include <stdio.h>

// int	ft_isascii(int c);

// int	main(void)
// {
// 	printf("'2': %d\n", ft_isascii('2'));
// 	printf("'c': %d\n", ft_isascii('c'));
// 	printf("'D': %d\n", ft_isascii('D'));
// 	printf("'\\n': %d\n", ft_isascii('\n'));
// 	printf("',': %d\n", ft_isascii(','));
// 	printf("' ': %d\n", ft_isascii(' '));
// 	printf("isalpha --------------------------\n");
// 	printf("'2': %d\n", isascii('2'));
// 	printf("'c': %d\n", isascii('c'));
// 	printf("'D': %d\n", isascii('D'));
// 	printf("'\\n': %d\n", isascii('\n'));
// 	printf("',': %d\n", isascii(','));
// 	printf("' ': %d\n", isascii(' '));
// 	return (0);
// }

#include <ctype.h>
#include <stdio.h>

int	ft_isascii(int c);

int	main(void)
{
	int	ch;

	for (ch = 0x7c; ch <= 0x82; ch++)
	{
		printf("%#04x    ", ch);
		if (isascii(ch))
			printf("The character is %c\n", ch);
		else
			printf("Cannot be represented by an ASCII character\n");
		if (ft_isascii(ch))
			printf("ft: 	The character is %c\n", ch);
		else
			printf("ft: 	Cannot be represented by an ASCII character\n");
	}
	return (0);
}
/************************************************
   The output should be:

0x7c    The character is @
0x7d    The character is '
0x7e    The character is =
0x7f    The character is "
0x80    Cannot be represented by an ASCII character
0x81    The character is a
0x82    The character is b

************************************************/
