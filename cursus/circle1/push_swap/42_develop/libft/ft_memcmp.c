/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/29 03:29:40 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/04/29 04:58:33 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

int	ft_memcmp(const void *b1, const void *b2, size_t len)
{
	unsigned const char	*b_1;
	unsigned const char	*b_2;
	size_t				i;

	b_1 = (unsigned const char *)b1;
	b_2 = (unsigned const char *)b2;
	i = 0;
	while (i < len)
	{
		if (b_1[i] != b_2[i])
			return (b_1[i] - b_2[i]);
		i++;
	}
	return (0);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	int	self;
	int	real;

	self = ft_memcmp("hea", "hez", 3);
	real = memcmp("hea", "hez", 3);
	printf("%d\n", self);
	printf("%d\n", real);
	return (0);
}
*/
