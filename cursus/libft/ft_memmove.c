/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/24 23:50:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/04/25 07:26:18 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void *ft_memmove(void *dst, const void *src, size_t len)
{
    unsigned char *d;
    unsigned char *s;
    size_t i;
    
    if (dst == src || len == 0)
        return dst;
    d = (unsigned char *)dst;
    s = (unsigned char *)src;
    i = 0;
    if (d < s) {
        while(i < len) {
            d[i] = s[i];
            i++;
        }
        return dst;
    }
    while(len > 0)
    {
        len--;
        d[len] = s[len];
    }
    return dst;
}