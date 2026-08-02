/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 14:26:57 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/08 15:27:39 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char		*d_char;
	const unsigned char	*s_char;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	if (dest == src || n == 0)
		return (dest);
	d_char = (unsigned char *)dest;
	s_char = (const unsigned char *)src;
	i = 0;
	if (d_char > s_char)
	{
		while (n--)
			d_char[n] = s_char[n];
	}
	else
	{
		while (i < n)
		{
			d_char[i] = s_char[i];
			i++;
		}
	}
	return (dest);
}
