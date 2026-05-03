/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:38:16 by htakumi           #+#    #+#             */
/*   Updated: 2026/05/03 12:10:14 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;
	size_t	llen;

	if (little[0] == '\0')
		return ((char *)big);
	i = 0;
	llen = 0;
	while (little[llen])
		llen++;
	while (i + llen <= len && big[i])
	{
		j = 0;
		while (j < llen && big[i + j] == little[j])
			j++;
		if (j == llen)
			return ((char *)big + i);
		i++;
	}
	return (NULL);
}
