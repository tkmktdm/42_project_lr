/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/07 21:13:43 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <stdio.h>

int ft_printf(const char *, ...)
{
    int s = 2;
    printf("%d", s);
    return 0;
}

int main() {
int s = 2;
printf("%c", 'a');
printf("%s", "aa");
printf("%p", 'a');
printf("%d", '1.3');
printf("%i", '2');
printf("%u", 'a');
printf("%x", 'a');
printf("%X", 'a');
printf("%%", 'a');
return 0;
}