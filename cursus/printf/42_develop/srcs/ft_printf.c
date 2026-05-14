/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/15 07:54:13 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "printf.h"
#include "../includes/ft_printf.h"

int ft_printf(const char *format, ...)
{
    va_list ap;
    int count;

    count = 0;
    va_start(ap, format);
    while(*format)
    {
        if (*format == '%')
        {
            format++;
            count += ft_handle_conversion(*format, &ap);
        }
        else
            count += write(1, format, 1);
        format++;
    }
    va_end(ap);
    return count;
}

int ft_handle_conversion(char c, va_list *ap)
{
    int i;

    i = 0;
    if(c == '%')
        write(1, "%", 1);
    else if (c == 's')
        ft_putstr_fd(va_arg(*ap, int), 1);
    else if (c == 'c')
        ft_putchar_fd(va_arg(*ap, int), 1);
    return ft_strlen(va_arg(*ap, int));
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
