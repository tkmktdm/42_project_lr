/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 10:33:41 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/25 11:21:40 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*p;
	size_t				i;
	unsigned char		ch;

	i = 0;
	ch = (unsigned char)c;
	p = (const unsigned char *)s;
	while (i < n)
	{
		if (*p == ch)
		{
			return ((void *)p);
		}
		p++;
		i++;
	}
	return (NULL);
}
