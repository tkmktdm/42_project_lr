/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 23:54:37 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/03/25 09:43:05 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int ft_strncmp(char *s1, char *s2, unsigned int n);

int ft_strncmp(char *s1, char *s2, unsigned int n) {
    while ((*s1 || *s2) && n) {
        if (*s1 > *s2) {
            return 1;
        } else if (*s1 < *s2) {
            return -1;
        }
        s1++;
        s2++;
        n--;
    }
    return 0;
}

int main() {
    int i;

    i = strncmp("hello", "hello", 3);
    printf("hello: 0 %d\n", i);
    i = strncmp("hello", "hoi", 2);
    printf("hello: -1 %d\n", i);
    i = strncmp("hello", "hai", 2);
    printf("hello: 1 %d\n", i);
    i = strncmp("hello", "hey", 2);
    printf("hello: 0 %d\n", i);
    printf("ft_strncmp--------\n");
    i = ft_strncmp("hello", "hello", 3);
    printf("hello: 0 %d\n", i);
    i = ft_strncmp("hello", "hoi", 2);
    printf("hello: -1 %d\n", i);
    i = ft_strncmp("hello", "hai", 2);
    printf("hello: 1 %d\n", i);
    i = ft_strncmp("hello", "hey", 2);
    printf("hello: 0 %d\n", i);
    return 0;
}