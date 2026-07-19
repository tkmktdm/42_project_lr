/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/18 23:10:23 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/20 14:15:22 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// 仮実装
#include <sys/fcntl.h>
#include <stdio.h>
#include "../42_develop/get_next_line.h"

int main () {
	// main.c (テスト用)
	int fd = open("test1_normal.txt", O_RDONLY);
	// int fd = open("test2_no_newline_at_end.txt", O_RDONLY);
	char *line;
    
    printf("--------");
    printf("%d", fd);
    printf("--------");
    if ((line = get_next_line(fd)) != NULL)
    {
        printf("%s", line);
    }
	// while ((line = get_next_line(fd)) != NULL)
	// {
	//     printf("%s", line);
	//     // free(line);
	// }
	close(fd);
}