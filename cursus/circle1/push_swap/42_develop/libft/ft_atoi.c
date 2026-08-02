/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 13:12:02 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/04 16:53:53 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	int		i;
	int		sign;
	long	re;

	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	re = 0;
	while (str[i] >= '0' && str[i] <= '9')
	{
		re = (re * 10) + (str[i] - '0');
		i++;
	}
	return ((int)(re * sign));
}
/*
#include <stdlib.h>
#include <stdio.h>

int	main(void)
{
	char	*int_min;

	int_min = "-2147483648";
	printf("%d\n", ft_atoi(int_min));
	printf("%d\n", atoi(int_min));
	return (0);
}
*/
