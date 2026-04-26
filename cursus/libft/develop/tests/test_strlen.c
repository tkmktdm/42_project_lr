/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_strlen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 14:20:02 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 14:35:26 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

// htakumiのヘッダがなければプロトタイプだけ宣言
size_t	ft_strlen(const char *s);

int	main(void)
{
	printf("'' -> ft:%zu std:%lu\n", ft_strlen(""), strlen(""));
	printf("'hello' -> ft:%zu std:%lu\n", ft_strlen("hello"), strlen("hello"));
	printf("'abc' -> ft:%zu std:%lu\n", ft_strlen("abc"), strlen("abc"));
	return (0);
}
