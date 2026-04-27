/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_atoi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:50:53 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 14:31:50 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>

// #include <string.h>

// htakumiのヘッダがなければプロトタイプだけ宣言
int	ft_atoi(const char *nptr);

int	main(void)
{
	printf("'' -> ft:%d std:%d\n", ft_atoi(""), atoi(""));
	printf("'hello' -> ft:%d std:%d\n", ft_atoi("+1hello"), atoi("+1hello"));
	printf("'abc' -> ft:%d std:%d\n", ft_atoi("123456789abc"),
		atoi("123456789abc"));
	printf("'1' -> ft:%d std:%d\n", ft_atoi("+"), atoi("+"));
	printf("'2' -> ft:%d std:%d\n", ft_atoi("-"), atoi("-"));
	printf("'3' -> ft:%d std:%d\n", ft_atoi("0"), atoi("0"));
	printf("'4' -> ft:%d std:%d\n", ft_atoi("1abc"), atoi("1abc"));
	printf("'5' -> ft:%d std:%d\n", ft_atoi("a1abc"), atoi("a1abc"));
	printf("'6' -> ft:%d std:%d\n", ft_atoi("+1+1abc"), atoi("+1+1abc"));
	printf("'7' -> ft:%d std:%d\n", ft_atoi("+11-1abc"), atoi("+11-1abc"));
	printf("'8' -> ft:%d std:%d\n", ft_atoi("-1"), atoi("-1"));
	printf("'9' -> ft:%d std:%d\n", ft_atoi("++1234"), atoi("++1234"));
	printf("'9' -> ft:%d std:%d\n", ft_atoi("--56789"), atoi("--56789"));
	return (0);
}
