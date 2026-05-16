/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_ptr.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/15 14:13:33 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

int ft_print_ptr(va_list *ap)
{
    int *p;

    p = va_arg(*ap, int);
    ft_putnbr_fd(p, 1);
    return ft_strlen(p);
}