/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/30 10:46:46 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/30 14:01:54 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <stdlib.h>

int	ft_atoi(char *str);

int	ft_atoi(char *str)
{
	int		mflg;
	long	n;

	n = 0;
	mflg = 0;
	while ((*str >= 9 && *str <= 13) || *str == ' ')
		str++;
	while (*str == '+' || *str == '-')
	{
		if (*str == '-')
			mflg++;
		str++;
	}
	while (*str >= '0' && *str <= '9')
	{
		n = n * 10 + (*str - '0');
		str++;
	}
	if (mflg % 2 == 1)
		n = -n;
	return (n);
}

// int	main(void)
// {
// 	printf("%d\n", ft_atoi(" a---+--+1234ab567"));
// 	printf("%d\n", ft_atoi(" --12-+--+1234ab567"));
// 	printf("%d\n", ft_atoi("  -12-+--+1234ab567"));
// 	printf("%d\n", ft_atoi("+-12345-+--+1234ab567"));
// 	printf("%d\n", ft_atoi("+12345-+--+1234ab567"));
// 	printf("%d\n", ft_atoi("-12345-+--+1234ab567"));
// 	printf("%d\n", ft_atoi("2147483647"));
// 	printf("%d\n", ft_atoi("2147483648"));
// 	printf("%d\n", ft_atoi("-2147483648"));
// 	printf("%d\n", ft_atoi("21474836480"));
// 	printf(" ------------------------ \n");
// 	// printf("%d\n", atoi(" a---+--+1234ab567"));
// 	// printf("%d\n", atoi(" --12-+--+1234ab567"));
// 	// printf("%d\n", atoi("  -12-+--+1234ab567"));
// 	// printf("%d\n", atoi("+-12345-+--+1234ab567"));
// 	// printf("%d\n", atoi("+12345-+--+1234ab567"));
// 	// printf("%d\n", atoi("-12345-+--+1234ab567"));
// 	// printf("%d\n", atoi("2147483647"));
// 	// printf("%d\n", atoi("2147483648"));
// 	// printf("%d\n", atoi("-2147483648"));
// 	// printf("%d\n", atoi("2147483648"));
// 	// return (0);
// }
