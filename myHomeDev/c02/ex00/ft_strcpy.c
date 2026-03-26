/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/22 14:14:29 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/24 17:12:19 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

char	*ft_strcpy(char *dest, char *src);

char	*ft_strcpy(char *dest, char *src)
{
	char	*temp;

	temp = dest;
	while (*src)
	{
		*temp = *src;
		temp++;
		src++;
	}
	*temp = '\0';
	return (dest);
}

// int	main(void)
// {
// 	char	dest[5];
// 	char	dest2[5];
// 	char	dest3[5];

// 	printf("strcpy---------------------\n");
// 	strcpy(dest, "Hey");
// 	strcpy(dest2, "Hello");
// 	strcpy(dest3, "Ohayo");
// 	printf("%s\n", dest);
// 	printf("%s\n", dest2);
// 	printf("%s\n", dest3);
// 	printf("strcpy end---------------------\n");
// 	printf("ft_strcpy---------------------\n");
// 	ft_strcpy(dest, "Hey");
// 	ft_strcpy(dest2, "Hello");
// 	ft_strcpy(dest3, "Ohayo");
// 	printf("%s\n", dest);
// 	printf("%s\n", dest2);
// 	printf("%s\n", dest3);
// 	return (0);
// }
