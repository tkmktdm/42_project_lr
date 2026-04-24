/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:38:37 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/24 12:18:13 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <string.h>

#define BUF_SIZE 16

void	*ft_memset(void *s, int c, size_t n);

int	main(void)
{
	char	buf1[BUF_SIZE];
	char	buf2[BUF_SIZE];

	// 変数定義
	// 変数初期化
	memset(buf1, '\0', BUF_SIZE);
	memset(buf2, '\0', BUF_SIZE);
	// 配列の内容を表示
	printf("初期化後の配列の要素を表示。\n");
	printf("buf1:%s\n", buf1);
	printf("buf2:%s\n", buf2);
	// メモリ領域を特定の文字で埋める
	memset(buf1, 'a', 4); // buf1の最初の4バイトをaにする
	memset(buf1, 'b', 2); // buf1の最初の2バイトをbにする
	memset(buf2, 'c', 3); // buf2の最初の3バイトをcにする
	// 配列の内容を表示
	printf("配列の要素を表示。\n");
	printf("buf1:%s\n", buf1);
	printf("buf2:%s\n", buf2);
	// ft_memset
	printf("ft_memset ---------- \n");
	// 変数定義
	// 変数初期化
	ft_memset(buf1, '\0', BUF_SIZE);
	ft_memset(buf2, '\0', BUF_SIZE);
	// 配列の内容を表示
	printf("初期化後の配列の要素を表示。\n");
	printf("buf1:%s\n", buf1);
	printf("buf2:%s\n", buf2);
	// メモリ領域を特定の文字で埋める
	ft_memset(buf1, 'a', 4); // buf1の最初の4バイトをaにする
	ft_memset(buf1, 'b', 2); // buf1の最初の2バイトをbにする
	ft_memset(buf2, 'c', 3); // buf2の最初の3バイトをcにする
	// 配列の内容を表示
	printf("配列の要素を表示。\n");
	printf("buf1:%s\n", buf1);
	printf("buf2:%s\n", buf2);
	return (0);
}
