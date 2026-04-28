/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:15:00 by kokubo            #+#    #+#             */
/*   Updated: 2026/04/28 22:19:53 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	size_t			total;
	unsigned char	*p;
	size_t			i;

	if (size != 0 && count > SIZE_MAX / size)
		return (NULL);
	total = count * size;
	p = (unsigned char *)malloc(total);
	if (!p)
		return (NULL);
	i = 0;
	while (i < total)
	{
		p[i] = 0;
		i++;
	}
	return ((void *)p);
}
