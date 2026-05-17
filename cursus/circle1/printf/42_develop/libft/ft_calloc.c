/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:48:50 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/28 22:20:09 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <limits.h>
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	*p;
	size_t			i;
	size_t			total;

	i = 0;
	if (size != 0 && count > (size_t)(-1) / size)
		return (NULL);
	total = count * size;
	p = (unsigned char *)malloc(total);
	if (!p)
		return (NULL);
	while (i < total)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
