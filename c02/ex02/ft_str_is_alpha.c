/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_alpha.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:20:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 09:01:09 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

int	ft_str_is_alpha(char *str);

int	ft_str_is_alpha(char *str)
{
	int	flg;

	flg = 1;
	while (*str)
	{
		if ((('a' <= *str) && (*str <= 'z')) || (('A' <= *str)
				&& (*str <= 'Z')))
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
// 	printf("HeLLoWorlD: %d\n", ft_str_is_alpha("HeLLoWorlD"));
// 	printf("helloworld: %d\n", ft_str_is_alpha("helloworld"));
// 	printf("HELLO: %d\n", ft_str_is_alpha("HELLO"));
// 	printf("Hello world: %d\n", ft_str_is_alpha("Hello world"));
// 	printf("Hello world2: %d\n", ft_str_is_alpha("Hello world2"));
// 	printf("123456: %d\n", ft_str_is_alpha("123456"));
// 	printf(": %d\n", ft_str_is_alpha(""));
// 	return (0);
// }
