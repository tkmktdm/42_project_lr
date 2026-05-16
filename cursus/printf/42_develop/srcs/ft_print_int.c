/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_int.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/16 08:59:48 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int ft_print_int(va_list *ap)
{
    int i;
    int len;
    char *str;

    i = va_arg(*ap, int);
    str = ft_itoa(i);
    ft_putnbr_fd(str, 1);
    len = ft_strlen(str);
    free(str);
    return len;
}