/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memmove.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 23:50:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/04/25 07:10:16 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

#include <stdio.h>
#include <string.h>

void *ft_memmove(void *dst, const void *src, size_t len);

#define BUF_SIZE 16

int main()
{
    // 変数定義
    char buf1[BUF_SIZE];
    char buf2[BUF_SIZE];

    // 変数初期化
    memset(buf1, '\0', BUF_SIZE);
    memset(buf2, '\0', BUF_SIZE);

    // メモリ領域を特定の文字で埋める
    memset(buf1, 'b', 4);  // buf1の最初の4バイトをaにする
    memset(buf1, 'a', 2);  // buf1の最初の2バイトをbにする

    // 配列の内容を表示
    printf("配列の要素を表示(コピー前)。\n");
    printf("buf1:%s\n", buf1);
    printf("buf2:%s\n", buf2);

    // メモリを上書きする
    memmove(buf2, buf1, 3);  // buf1の先頭3バイトをbuf2に上書きする
    memmove(&buf1[2], &buf1[0], 3);  // buf1の先頭3バイトをbuf1の3バイト目に上書きする

    // 配列の内容を表示
    printf("配列の要素を表示(コピー後)。\n");
    printf("buf1:%s\n", buf1);
    printf("buf2:%s\n", buf2);

    return 0;
}