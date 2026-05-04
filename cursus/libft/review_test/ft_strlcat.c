/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:13:18 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/03 17:45:45 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t strlcat(char *dst, const char *src, size_t dstsize)
{
    size_t i;
    size_t dlen;
    size_t slen;
    
    dlen = ft_strlen(dst);
    slen = ft_strlen(src);
    i = 0;

    if(dstsize <= dlen)
        return dstsize + slen;
    while((dlen + i) < (dstsize - 1) && src[i])
    {
        dst[dlen+i] = src[i];
        i++;
    }
    dst[dlen + i] = '\0';
    return dlen+slen;
}
