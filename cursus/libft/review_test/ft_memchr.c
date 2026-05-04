/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:13:18 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/03 14:30:05 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void *ft_memchr(const void *s, int c, size_t n)
{
    size_t i;
    unsigned char *p;

    i = -1;
    p = (unsigned char *)s;
    while (++i < n)
        if (p[i] == (unsigned char)c)
            return p+i;
    return NULL;
}