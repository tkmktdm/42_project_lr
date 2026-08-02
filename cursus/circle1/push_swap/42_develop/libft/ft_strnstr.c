/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 04:57:39 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/04/30 03:33:21 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	if (*little == '\0')
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		j = 0;
		while (little[j] && big[i + j] == little[j] && (j + i) < len)
			j++;
		if (little[j] == '\0')
			return ((char *)&big[i]);
		i++;
	}
	return (NULL);
}
/*
#include <string.h>
#include <stdio.h>

int	main(void) {
	const char *text = "Hello, world!aa";
	const char *text1 = "Hello, world!aa";
	const char *search = "world";
	const char *search1 = "world";

	char *result = strnstr(text, search, 14);
	char *result1 = ft_strnstr(text1, search1, 14);

	printf("%s\n", result);
	printf("%s\n", result1);
	return (0);
}
*/
