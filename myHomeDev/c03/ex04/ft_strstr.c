/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 14:09:27 by htakumi           #+#    #+#             */
/*   Updated: 2026/03/25 14:40:59 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

char	*ft_strstr(char *str, char *to_find);

char	*ft_strstr(char *str, char *to_find)
{
	char	*temp;
	char	*find_pointer;
	int		flg;

	flg = 0;
	*temp = *to_find;
	while (*str++)
	{
		if (*str == *temp)
		{
			if (flg == 0)
			{
				*find_pointer = *temp;
				flg = 1;
			}
			temp++;
		}
		else if (flg && *temp == '\0')
			return (find_pointer);
		else
		{
			flg = 0;
		}
	}
	return ("nil");
}

int	main(void)
{
	char	c[20];
	char	*pos;
	char	*pos1;
	char	*pos2;
	char	*pos3;

	c[0] = 'H';
	c[1] = 'e';
	c[2] = 'l';
	c[3] = 'l';
	c[4] = 'o';
	pos = NULL;
	pos1 = NULL;
	pos2 = NULL;
	pos3 = NULL;
	pos = strstr(c, "Hello");
	pos1 = strstr(c, "Hello world");
	pos2 = strstr(c, "ll");
	pos3 = strstr(c, "aiueo");
	printf("c pointer------------------------\n");
	printf("%c: %p\n", c[0], &c[0]);
	printf("%c: %p\n", c[1], &c[1]);
	printf("%c: %p\n", c[2], &c[2]);
	printf("%c: %p\n", c[3], &c[3]);
	printf("%c: %p\n", c[4], &c[4]);
	printf("strstr------------------------\n");
	printf("%p\n", pos);
	printf("%p\n", pos1);
	printf("%p\n", pos2);
	printf("%p\n", pos3);
	pos = ft_strstr(c, "Hello");
	pos1 = ft_strstr(c, "Hello world");
	pos2 = ft_strstr(c, "ll");
	pos3 = ft_strstr(c, "aiueo");
	printf("ft_strstr------------------------\n");
	printf("%p\n", pos);
	printf("%p\n", pos1);
	printf("%p\n", pos2);
	printf("%p\n", pos3);
	return (0);
}
