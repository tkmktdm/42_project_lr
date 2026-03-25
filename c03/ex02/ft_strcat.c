/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/25 09:43:47 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/03/25 09:58:13 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include<stdio.h>

// char *ft_strcat(char *dest, char *src);

// char *ft_strcat(char *dest, char *src) {
//     return ;
// }

int main () {
    char *c;
    
    c = "Hello";
    strcat(c, "World");

    printf("%s\n", c);
    
    return 0;
}