/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/23 17:08:50 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strcount(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0' && s[i] != '\n')
		i++;
    if (s[i] == '\n')
		i++;
	return (i);
}

// 1. leftoverに\nがあるか探す
char  *ft_strchr_gnl(char *s, int c)
{
    return "";
}

// 2. leftoverから\nまでを切り出す（返す用）
char  *extract_line(char *leftover)
{
    char *line;
    int i;
    int len;
    
    i = 0;
    len = ft_strcount(leftover);
    line = malloc(sizeof(char) * len + 1);
    if (!line)
        return 0;

    while (leftover[i] != '\n' || leftover[i] != '\0')
    {
        line[i] = leftover[i];
        i++;
    }
    return line;
}

// 3. \nより後ろだけ残す（次回用）
char  *update_leftover(char *leftover)
{
    return "";
}