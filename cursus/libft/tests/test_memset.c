/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_memset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/23 17:38:37 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/23 23:37:06 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void ft_memset(void *b, int c, size_t len);

int main () {
    int arr[10];
    memset(arr, 0, sizeof(arr)); // すべての要素を0にする
    return 0;
}