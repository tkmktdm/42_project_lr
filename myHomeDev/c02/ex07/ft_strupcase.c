/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strupcase.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:20:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/26 13:08:02 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

char	*ft_strupcase(char *str);

char	*ft_strupcase(char *str)
{
	char	*temp;
	int		diff;

	temp = str;
	while (*temp)
	{
		if (('a' <= *temp) && (*temp <= 'z'))
		{
			*temp -= 'a' - 'A';
		}
		temp++;
	}
	return (str);
}

// int	main(void)
// {
// 	char	s1[] = "HeLLoWorlD";
// 	char	s2[] = "helloworld";
// 	char	s3[] = "HELLO";
// 	char	s4[] = "Hello2 world";

// 	printf("%s\n", ft_strupcase(s1));
// 	printf("%s\n", ft_strupcase(s2));
// 	printf("%s\n", ft_strupcase(s3));
// 	printf("%s\n", ft_strupcase(s4));
// 	return (0);
// }
