/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:54:37 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/03/29 21:15:52 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

int	ft_strncmp(char *s1, char *s2, unsigned int n);

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	while ((*s1 || *s2) && n)
	{
		if (*s1 > *s2)
		{
			return (*s1 - *s2);
		}
		else if (*s1 < *s2)
		{
			return (*s1 - *s2);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

// int	main(void)
// {
// 	int	i;

// 	i = strncmp("hello", "hello", 3);
// 	printf("hello: 0 %d\n", i);
// 	i = strncmp("hello", "hoi", 2);
// 	printf("hello: -1 %d\n", i);
// 	i = strncmp("hello", "hai", 2);
// 	printf("hello: 1 %d\n", i);
// 	i = strncmp("hello", "hey", 2);
// 	printf("hello: 0 %d\n", i);
// 	printf("ft_strncmp--------\n");
// 	i = ft_strncmp("hello", "hello", 3);
// 	printf("hello: 0 %d\n", i);
// 	i = ft_strncmp("hello", "hoi", 2);
// 	printf("hello: -1 %d\n", i);
// 	i = ft_strncmp("hello", "hai", 2);
// 	printf("hello: 1 %d\n", i);
// 	i = ft_strncmp("hello", "hey", 2);
// 	printf("hello: 0 %d\n", i);
// 	return (0);
// }
