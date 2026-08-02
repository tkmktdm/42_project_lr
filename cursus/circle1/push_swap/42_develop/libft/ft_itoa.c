/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 07:40:23 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/08 10:32:33 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdlib.h>

static int	ft_digits(long *nb)
{
	int		count;
	long	tmp;

	count = 0;
	if (*nb < 0)
	{
		*nb *= -1;
		count++;
	}
	tmp = *nb;
	while (tmp > 0)
	{
		count++;
		tmp /= 10;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	long	nb;
	char	*str;
	int		count;
	int		sign;

	nb = n;
	if (nb == 0)
		return (ft_strdup("0"));
	sign = 1;
	if (nb < 0)
		sign = -1;
	count = ft_digits(&nb);
	str = (char *)malloc(count + 1);
	if (!str)
		return (NULL);
	if (sign == -1)
		str[0] = '-';
	str[count--] = '\0';
	while (nb > 0)
	{
		str[count--] = (nb % 10) + '0';
		nb /= 10;
	}
	return (str);
}

/*
#include <stdio.h>

int	main(void)
{
	char	*str;
	int		n;

	n = -2147483648;
	str = ft_itoa(n);
	printf("%s\n", str);
	free(str);
	return (0);
}
*/
