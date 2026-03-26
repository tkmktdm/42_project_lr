/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_uppercase.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:20:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/26 12:27:33 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_str_is_uppercase(char *str);

int	ft_str_is_uppercase(char *str)
{
	int	flg;

	flg = 1;
	while (*str)
	{
		if (('A' <= *str) && (*str <= 'Z'))
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
// 	printf("HeLLoWorlD: %d\n", ft_str_is_uppercase("HeLLoWorlD"));
// 	printf("helloworld: %d\n", ft_str_is_uppercase("helloworld"));
// 	printf("HELLO: %d\n", ft_str_is_uppercase("HELLO"));
// 	printf("Hello world: %d\n", ft_str_is_uppercase("Hello world"));
// 	printf("Hello world2: %d\n", ft_str_is_uppercase("Hello world2"));
// 	printf("123456: %d\n", ft_str_is_uppercase("123456"));
// 	return (0);
// }
