/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 02:55:18 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/04/29 03:27:15 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memchr(const void *b, int c, size_t len)
{
	unsigned const char	*b2;
	unsigned char		c2;
	size_t				i;

	i = 0;
	b2 = (unsigned const char *)b;
	c2 = (unsigned char)c;
	while (i < len)
	{
		if (b2[i] == c2)
			return ((void *)&b2[i]);
		i++;
	}
	return (NULL);
}
/*
#include <stdio.h>
#include <string.h>

int main()
{
	char	*str;
	char	*str1;

	str = ft_memchr("Hello", 'o', 0);
	str1 = memchr("Hello", 'o', 0);
	printf("%s\n", str);
	printf("%s\n", str1);
	return 0;
}
*/
