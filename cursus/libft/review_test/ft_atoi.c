/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/03 14:13:18 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/03 17:49:04 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int ft_atoi(const char *str)
{
    int n;
    int mflg;
    
    n = 0;
    mflg = 1;
    while(*str >= 9 && *str <= 13 || *str == ' ')
        str++;
    if (*str == '+' || *str == '-')
    {
        if (*str == '-')
            mflg = -1;
        str++;
    }
    while(*str >= '0' && '9' >= *str)
    {
        n = (n * 10) + (*str - '0');
        str++;
    }
    return n * mflg;
}
