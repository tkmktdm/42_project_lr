/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_hex.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/15 14:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/16 09:43:41 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "printf.h"

void	ft_putnbr_base(int nbr, char *base);

int ft_print_hex(va_list *ap, int upper)
{
    int nbr;
    int len;
    char *str;

    nbr = va_arg(*ap, int);
    if (upper)
        ft_putnbr_base(nbr, "0123456789ABCDEF");
    else
        ft_putnbr_base(nbr, "0123456789abcdef");
    str = ft_itoa(nbr);
    ft_putnbr_fd(str, 1);
    len = ft_strlen(str);
    free(str);
    return len;
}