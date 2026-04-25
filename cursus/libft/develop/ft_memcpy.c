/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 12:23:27 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/24 13:00:01 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*p;
	const unsigned char	*s;
	size_t				i;

	if (n == 0)
		return (dest);
	i = 0;
	p = (unsigned char *)dest;
	s = (const unsigned char *)src;
	while (i < n)
	{
		*p = *s;
		i++;
		p++;
		s++;
	}
	return (dest);
}
