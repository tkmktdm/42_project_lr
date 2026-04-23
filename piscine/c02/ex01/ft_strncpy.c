/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:14:29 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 09:01:07 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>
// #include <unistd.h>

char	*ft_strncpy(char *dest, char *src, unsigned int n);

char	*ft_strncpy(char *dest, char *src, unsigned int n)
{
	char			*temp;
	unsigned int	i;

	i = 0;
	temp = dest;
	while (i < n && *src != '\0')
	{
		*temp = *src;
		temp++;
		src++;
		i++;
	}
	while (i < n)
	{
		*temp = '\0';
		i++;
		temp++;
	}
	return (dest);
}

// int	main(void)
// {
// 	char	dest[20];
// 	char	dest2[20];
// 	char	dest3[20];

// 	strncpy(dest, "Hello world", sizeof(dest) - 1);
// 	strncpy(dest2, "KONBANWA!!", 4);
// 	strncpy(dest3, "Ohayo", 8);
// 	printf("strncpy------------------------\n");
// 	printf("%s\n", dest);
// 	printf("%s\n", dest2);
// 	printf("%s\n", dest3);
// 	ft_strncpy(dest, "Hello world", sizeof(dest) - 1);
// 	ft_strncpy(dest2, "KONBANWA!!", 4);
// 	ft_strncpy(dest3, "Ohayo", 8);
// 	printf("ft_strncpy------------------------\n");
// 	printf("%s\n", dest);
// 	printf("%s\n", dest2);
// 	printf("%s\n", dest3);
// 	return (0);
// }
