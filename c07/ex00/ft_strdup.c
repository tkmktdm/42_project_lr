/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/01 11:14:18 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/02 17:23:05 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <unistd.h>
#include <stdlib.h>

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*p;
	int		len;
	int		i;

	i = 0;
	len = ft_strlen(src);
	p = malloc(sizeof(char) * (len + 1));
	if (p == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		p[i] = src[i];
		i++;
	}
	p[len] = '\0';
	return (p);
}

// int	main(void)
// {
// 	char	src[10] = "hello";
// 	char	*dest;

// 	dest = ft_strdup(src);
// 	printf("src: %s\n", src);
// 	printf("src: %p\n", src);
// 	printf("dest: %s\n", dest);
// 	printf("dest: %p\n", dest);
// 	free(dest);
// 	return (0);
// }
