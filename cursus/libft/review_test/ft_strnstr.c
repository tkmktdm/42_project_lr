/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:13:18 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/03 18:08:45 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char *strnstr(const char *big, const char *little, size_t len)
{
    int i;
    int j;
    
    i = 0;
    if (little[0] == '\0')
        return (char *)big;
    while (big[i])
    {
        j = 0;
        if (big[i] == little[j])
        {
            while (little[j] != '\0' && (i + j) < len && big[i+j] == little[j])
                j++;
            if (little[j] == '\0')
                return (char *)big+i;
        }
        i++;
    }
    
    return NULL;
}