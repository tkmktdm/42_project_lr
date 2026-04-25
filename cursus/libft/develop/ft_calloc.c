/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 12:48:50 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/25 13:03:32 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

void	*ft_calloc(size_t count, size_t size)
{
	unsigned char	**p;
	unsigned char	*w;
	size_t			i;
	size_t			j;

	i = 0;
	p = malloc(sizeof(char *) * count);
	if (!p)
		return (NULL);
	while (i < count)
	{
		w = malloc(sizeof(char) * size);
		if (!w)
			return (NULL);
		j = 0;
		while (j < size)
		{
			w[j] = 0;
			j++;
		}
		i++;
	}
	return ((void *)p);
}
