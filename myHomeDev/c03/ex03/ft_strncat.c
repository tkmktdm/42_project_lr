/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 13:57:45 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/25 14:08:28 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

char	*ft_strncat(char *dest, char *src, unsigned int nb);

char	*ft_strncat(char *dest, char *src, unsigned int nb)
{
	char	*temp;

	*temp = *dest;
	while (*temp)
	{
		temp++;
	}
	while (*src && nb > 0)
	{
		*temp = *src;
		temp++;
		src++;
		nb--;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	c[20];
// 	char	c1[20];

// 	c[0] = 'H';
// 	c[1] = 'e';
// 	c[2] = 'l';
// 	c[3] = 'l';
// 	c[4] = 'o';
// 	c1[0] = 'H';
// 	c1[1] = 'e';
// 	c1[2] = 'l';
// 	c1[3] = 'l';
// 	c1[4] = 'o';
// 	strncat(c, "world", 2);
// 	printf("strncat 2: %s\n", c);
// 	strncat(c1, "world", 2);
// 	printf("ft_strncat 2: %s\n", c1);
// 	return (0);
// }
