/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kokubo <kokubo@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/22 20:15:00 by kokubo            #+#    #+#             */
/*   Updated: 2026/04/23 01:00:00 by kokubo           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static size_t	num_len(int n)
{
	size_t	len;

	if (n == 0)
		return (1);
	len = 0;
	if (n < 0)
		len++;
	while (n != 0)
	{
		n /= 10;
		len++;
	}
	return (len);
}

static void	fill_abs(unsigned int n, char *r, size_t end)
{
	while (end > 0)
	{
		end--;
		r[end] = '0' + (n % 10);
		n /= 10;
	}
}

char	*ft_itoa(int n)
{
	size_t			len;
	unsigned int	abs_n;
	char			*r;

	len = num_len(n);
	r = (char *)malloc(len + 1);
	if (!r)
		return (NULL);
	r[len] = '\0';
	if (n < 0)
	{
		r[0] = '-';
		abs_n = -(unsigned int)n;
		fill_abs(abs_n, r + 1, len - 1);
	}
	else
	{
		fill_abs((unsigned int)n, r, len);
	}
	return (r);
}
