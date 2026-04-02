/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_str_is_printable.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:20:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/27 09:13:54 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <unistd.h>

int	ft_str_is_printable(char *str);

int	ft_str_is_printable(char *str)
{
	int	flg;

	flg = 1;
	while (*str)
	{
		if ((32 <= *str) && (*str <= 126))
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
// 	int	i;

// 	i = 0;
// 	printf("HeLLoWorlD: %d\n", ft_str_is_printable("HeLLoWorlD"));
// 	printf("helloworld: %d\n", ft_str_is_printable("helloworld"));
// 	printf("HELLO: %d\n", ft_str_is_printable("HELLO"));
// 	printf("Hello world: %d\n", ft_str_is_printable("Hello world"));
// 	printf("Hello world2: %d\n", ft_str_is_printable("Hello world2"));
// 	printf("123456: %d\n", ft_str_is_printable("123456"));
// 	return (0);
// }
