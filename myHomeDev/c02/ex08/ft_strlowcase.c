/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlowcase.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 18:20:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/26 22:35:19 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>

char	*ft_strlowcase(char *str);

char	*ft_strlowcase(char *str)
{
	char	*temp;

	temp = str;
	while (*temp)
	{
		if (('A' <= *temp) && (*temp <= 'Z'))
		{
			*temp += 'a' - 'A';
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

// 	printf("%s\n", ft_strlowcase(s1));
// 	printf("%s\n", ft_strlowcase(s2));
// 	printf("%s\n", ft_strlowcase(s3));
// 	printf("%s\n", ft_strlowcase(s4));
// 	return (0);
// }
