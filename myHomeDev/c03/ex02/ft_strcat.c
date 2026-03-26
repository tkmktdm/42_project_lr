/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:43:47 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/03/25 14:07:32 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

char	*ft_strcat(char *dest, char *src);

char	*ft_strcat(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	while (*temp)
	{
		temp++;
	}
	while (*src)
	{
		*temp = *src;
		temp++;
		src++;
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
// 	strcat(c, "World");
// 	printf("%s\n", c);
// 	ft_strcat(c1, "42Tokyo");
// 	printf("%s\n", c1);
// 	return (0);
// }
