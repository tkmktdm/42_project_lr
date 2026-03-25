/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 22:57:36 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/03/24 23:52:52 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>
#include <stdio.h>

int ft_strcmp(char *s1, char *s2);

int ft_strcmp(char *s1, char *s2) {
    while (*s1 || *s2) {
        if (*s1 > *s2) {
            return 1;
        } else if (*s2 > *s1) {
            return -1;
        }
        s1++;
        s2++;
    }
    return 0;
}

int main () {
    int i;

    // 完全一致なので0
    i = strcmp("hello", "hello");
    printf("hello 0: %d\n", i);
    // 第一引数が第二引数よりも辞書順で後に来るので正の値(1)
    i = strcmp("hello", "hai");
    printf("hello 1: %d\n", i);
    // 第一引数が第二引数よりも辞書順で前に来るので負の値(-1)
    i = strcmp("hello", "hoi");
    printf("hello -1: %d\n", i);
    // 第一引数の最後の文字('\0'=0)が第二引数('l')よりも辞書順で前に来るので負の値(-1)
    i = strcmp("he -1", "hello");
    printf("he: %d\n", i);

    // 完全一致なので0
    i = ft_strcmp("hello", "hello");
    printf("hello 0: %d\n", i);
    // 第一引数が第二引数よりも辞書順で後に来るので正の値(1)
    i = ft_strcmp("hello", "hai");
    printf("hello 1: %d\n", i);
    // 第一引数が第二引数よりも辞書順で前に来るので負の値(-1)
    i = ft_strcmp("hello", "hoi");
    printf("hello -1: %d\n", i);
    // 第一引数の最後の文字('\0'=0)が第二引数('l')よりも辞書順で前に来るので負の値(-1)
    i = ft_strcmp("he", "hello");
    printf("he -1: %d\n", i);
    return 0;
}