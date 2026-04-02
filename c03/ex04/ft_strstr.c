/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:09:27 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/29 15:30:44 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include <stdio.h>
// #include <string.h>

char	*ft_strstr(char *str, char *to_find);

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

int	ft_strncmp(char *s1, char *s2, unsigned int n)
{
	while ((*s1 || *s2) && n)
	{
		if (*s1 > *s2)
		{
			return (1);
		}
		else if (*s1 < *s2)
		{
			return (-1);
		}
		s1++;
		s2++;
		n--;
	}
	return (0);
}

char	*ft_strstr(char *str, char *to_find)
{
	int	find_size;

	find_size = ft_strlen(to_find);
	if (find_size == 0)
	{
		return (str);
	}
	while (*str)
	{
		if (ft_strncmp(str, to_find, find_size) == 0)
			return (str);
		str++;
	}
	return (0);
}

// int	main(void)
// {
// 	char	c[20];
// 	char	*pos;
// 	char	*pos1;
// 	char	*pos2;
// 	char	*pos3;

// 	c[0] = 'H';
// 	c[1] = 'e';
// 	c[2] = 'l';
// 	c[3] = 'l';
// 	c[4] = 'o';
// 	pos = NULL;
// 	pos1 = NULL;
// 	pos2 = NULL;
// 	pos3 = NULL;
// 	pos = strstr(c, "Hello");
// 	pos1 = strstr(c, "Hello world");
// 	pos2 = strstr(c, "ll");
// 	pos3 = strstr(c, "aiueo");
// 	printf("c pointer------------------------\n");
// 	printf("%c: %p\n", c[0], &c[0]);
// 	printf("%c: %p\n", c[1], &c[1]);
// 	printf("%c: %p\n", c[2], &c[2]);
// 	printf("%c: %p\n", c[3], &c[3]);
// 	printf("%c: %p\n", c[4], &c[4]);
// 	printf("' ' vs ' ': %p\n", strstr("", ""));
// 	printf("strstr------------------------\n");
// 	printf("%p\n", pos);
// 	printf("%p\n", pos1);
// 	printf("%p\n", pos2);
// 	printf("%p\n", pos3);
// 	pos = ft_strstr(c, "Hello");
// 	pos1 = ft_strstr(c, "Hello world");
// 	pos2 = ft_strstr(c, "ll");
// 	pos3 = ft_strstr(c, "aiueo");
// 	printf("ft_strstr------------------------\n");
// 	printf("%p\n", pos);
// 	printf("%p\n", pos1);
// 	printf("%p\n", pos2);
// 	printf("%p\n", pos3);
// 	printf("' ' vs ' ': %p\n", ft_strstr("", ""));
// 	return (0);
// }
