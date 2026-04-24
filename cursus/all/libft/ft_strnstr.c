/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokubo <kokubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:15:00 by kokubo            #+#    #+#             */
/*   Updated: 2026/04/23 01:00:00 by kokubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	nlen;
	size_t	i;
	size_t	j;

	if (needle[0] == '\0')
		return ((char *)haystack);
	nlen = 0;
	while (needle[nlen])
		nlen++;
	i = 0;
	while (i + nlen <= len && haystack[i])
	{
		j = 0;
		while (j < nlen && haystack[i + j] == needle[j])
			j++;
		if (j == nlen)
			return ((char *)&haystack[i]);
		i++;
	}
	return (NULL);
}
