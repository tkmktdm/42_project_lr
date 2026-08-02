/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_atoi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfujikaw <tfujikaw@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/10 20:31:48 by tfujikaw          #+#    #+#             */
/*   Updated: 2026/05/10 20:47:28 by tfujikaw         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_atoi(const char *str)
{
	long	re;
	int		sign;
	int		i;

	i = 0;
	sign = 1;
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
#include <stdio.h>
#include <stdlib.h>

int main()
{
	int i;
	int b;

	i = ft_atoi("  -12345abc");
	b = atoi("  -12345abc");
	printf("%d\n", i);
	printf("%d\n", b);
	return 0;
}
*/
