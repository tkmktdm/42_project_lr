/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_percent.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/15 14:16:04 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>
#include "printf.h"
#include "../includes/ft_printf.h"

int ft_print_percent(va_list *ap)
{
    ft_putchar_fd('%', 1);
    return (1);
}

// int ft_printf_char_write(char c, va_list *ap)
// {
//     int i;

//     i = 0;
//     if(c == '%')
//         write(1, "%", 1);
//     else if (c == 's')
//         ft_putstr_fd(va_arg(*ap, int), 1);
//     else if (c == 'c')
//         ft_putchar_fd(va_arg(*ap, int), 1);
//     return 0;
// }