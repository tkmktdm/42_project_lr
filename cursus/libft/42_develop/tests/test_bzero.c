/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bzero.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 13:50:53 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/24 11:02:22 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <strings.h>

// htakumiのヘッダがなければプロトタイプだけ宣言
void	ft_bzero(void *s, size_t n);

void	print_memory(const char *label, unsigned char *ptr, size_t size)
{
	printf("%s: ", label);
	for (size_t i = 0; i < size; i++)
	{
		// %02X で16進数表示（0x00のように見える）
		// 文字列として見たい場合は %c ですが、0は表示されません
		printf("[%02X] ", ptr[i]);
	}
	printf("\n");
}

int	main(void)
{
	char buf[10] = "ABCDE"; // 初期データ
	print_memory("bzero: 実行前", (unsigned char *)buf, sizeof(buf));
	// 先頭から5バイト分を0で埋める
	bzero(buf, 5);
	print_memory("bzero: 実行後", (unsigned char *)buf, sizeof(buf));
	// ft_bzero
	char ft_buf[10] = "HELLO"; // 初期データ
	print_memory("ft_bzero: 実行前", (unsigned char *)ft_buf, sizeof(ft_buf));
	// 先頭から5バイト分を0で埋める
	ft_bzero(ft_buf, 5);
	print_memory("ft_bzero: 実行後", (unsigned char *)ft_buf, sizeof(ft_buf));
	return (0);
}
