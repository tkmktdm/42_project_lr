/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_lowercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:20:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 08:52:22 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_str_is_lowercase(char *str);

int	ft_str_is_lowercase(char *str)
{
	int	flg;

	flg = 1;
	while (*str)
	{
		if (('a' <= *str) && (*str <= 'z'))
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
// 	printf("HeLLoWorlD: %d\n", ft_str_is_lowercase("HeLLoWorlD"));
// 	printf("helloworld: %d\n", ft_str_is_lowercase("helloworld"));
// 	printf("HELLO: %d\n", ft_str_is_lowercase("HELLO"));
// 	printf("Hello world: %d\n", ft_str_is_lowercase("Hello world"));
// 	printf("Hello world2: %d\n", ft_str_is_lowercase("Hello world2"));
// 	printf("123456: %d\n", ft_str_is_lowercase("123456"));
// 	return (0);
// }
