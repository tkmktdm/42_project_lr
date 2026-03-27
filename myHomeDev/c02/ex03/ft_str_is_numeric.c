/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_numeric.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/26 11:27:43 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 08:52:19 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_str_is_numeric(char *str);

int	ft_str_is_numeric(char *str)
{
	int	flg;

	flg = 1;
	while (*str)
	{
		if (('0' <= *str) && (*str <= '9'))
		{
			flg = 1;
			str++;
		}
		else
		{
			return (0);
		}
	}
	return (flg);
}

// int	main(void)
// {
// 	printf("HeLLoWorlD: %d\n", ft_str_is_numeric("HeLLoWorlD"));
// 	printf("helloworld: %d\n", ft_str_is_numeric("helloworld"));
// 	printf("HELLO: %d\n", ft_str_is_numeric("HELLO"));
// 	printf("Hello world: %d\n", ft_str_is_numeric("Hello world"));
// 	printf("Hello world2: %d\n", ft_str_is_numeric("Hello world2"));
// 	printf("123456: %d\n", ft_str_is_numeric("123456"));
// 	return (0);
// }
