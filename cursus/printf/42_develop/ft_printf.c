/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/12 09:21:30 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "printf.h"

size_t	ft_strcount(const char *s, char word)
{
	size_t	len;

	len = 0;
	while (*s)
	{
		if (*s == word)
			len++;
		s++;
	}
	return (len);
}

int ft_printf(const char *format, ...)
{
/**
 * 可変引数の要素１つずつ取り出す方法
 * 最初の引数は呼び出した第一引数のもので呼べるが
 * 第二引数以降はva_arg(ap, type)の形でアクセスする必要がある
    fmt = (char *)format;
    va_start(ap, fmt);
    printf("fmt: %s\n", fmt);
    printf("fmt: %s\n", va_arg(ap, char*));
    va_end(ap);
*/
    va_list ap;
    char *fmt;
    int split;

    fmt = (char *)format;
    va_start(ap, fmt);

    split = ft_strcount(fmt, '%');
    printf("%d-----", split);
    // while(fmt != NULL)
    // {
    //     while (*fmt != '\0')
    //     {
    //         write(1, fmt, 1);
    //         fmt++;
    //     }
    //     fmt = va_arg(ap, char*);
    // }
    va_end(ap);
    return 0;
}

int main() {
    int s = 2;
    // ft_printf("h%e%%l%lo\n", "world");
    // printf("%s", "aa");
    // printf("%p", 'a');
    // printf("%d", '1.3');
    // printf("%i", '2');
    // printf("%u", 'a');
    // printf("%x", 'a');
    // printf("%X", 'a');
    // printf("%%", 'a');
    
    // printf("--------\n");
    // int count = printf("%s\n", "aaa");
    // printf("aaa", "bbb");
    // printf("-\n");
    // printf("%");
    // printf("--\n");
    // printf("%%");
    // printf("---\n");
    printf("%%%");
    printf("----\n");
    printf("%%%%");
    // printf("count: %d\n", count);

    return 0;
}

// %が出てきた時に次の文字を見る
// 1. 1文字の時はそのまま出力
// 2. 2文字の時は
