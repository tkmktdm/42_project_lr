/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hibitakumi <hibitakumi@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/05/21 07:58:32 by hibitakumi       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include<stdio.h>
#define BUF_SIZE 512
// fileが読まれると3が入る
char *get_next_line(int fd)
{
	int byte_num;
	char buf[BUF_SIZE];
	int i;
	
	i = 0;
	if (fd == -1)
		return NULL;
	// ファイルから5バイト読み込み
    byte_num = read(fd, &buf[0], BUF_SIZE);  // ファイルから5バイト読み込み
	// printf("%d\n", byte_num);
    if(byte_num == -1)  // ファイル読み込み失敗
    {
        fprintf(stdout, "ファイル読み込みエラー\n");
        return NULL;
    }
	while (buf[i])
	{
		write(1, &buf[i], 1);
		i++;
	}
	return ("s");
}
