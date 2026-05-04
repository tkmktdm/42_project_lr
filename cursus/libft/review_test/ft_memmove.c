/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:13:18 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/03 17:12:44 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memmove(void *dst, const void *src, size_t len)
{
    unsigned char *d;
    unsigned char *s;
    size_t i;

    d = (unsigned char *)dst;
    s = (unsigned char *)src;
    i = 0;
    if (d > s)
    {
        while (len)
        {
            len--;
            d[len] = s[len];
        }
    }
    if (d < s)
    {
        while (i < len)
        {
            d[i] = s[i];
            i++;
        }
    }
    return d;
}