/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/13 23:55:29 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "printf.h"
#include "../includes/ft_printf.h"

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
    va_list ap;
    char *fmt;

    fmt = (char *)format;
    va_start(ap, fmt);
    while(*fmt != '\0')
    {
        if (*fmt == '%')
        {
            fmt++;
            ft_handle_conversion(*fmt, &ap);
        }
        else
            write(1, fmt, 1);
        fmt++;
    }
    va_end(ap);
    return 0;
}

void ft_handle_conversion(char c, va_list *ap)
{
    if(c == '%')
        write(1, c, 1);
    else if (c == 's')
    {
        ft_put
    }
}

int main() {
    int s = 2;
    ft_printf("%s\n", "wolrd");
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
    // printf("%%%");
    // printf("----\n");
    // printf("%%%%");
    // printf("count: %d\n", count);

    return 0;
}

// %が出てきた時に次の文字を見る
// 1. 1文字の時はそのまま出力
// 2. 2文字の時は
