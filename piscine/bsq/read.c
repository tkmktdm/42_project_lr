/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/08 20:46:41 by htakumi           #+#    #+#             */
/*   Updated: 2026/04/08 21:01:29 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bsq.h"

static void	ft_memcpy_s(char *dst, char *src, int n)
{
	int	i;

	if (!dst || !src || n <= 0)
		return ;
	i = 0;
	while (i < n)
	{
		dst[i] = src[i];
		i++;
	}
}

char	*read_fd(int fd)
{
	char	*content;
	char	*tmp;
	char	buf[4096];
	int		n;
	int		total;

	content = NULL;
	total = 0;
	n = read(fd, buf, 4096);
	while (n > 0)
	{
		tmp = malloc(total + n + 1);
		if (!tmp)
			return (free(content), NULL);
		ft_memcpy_s(tmp, content, total);
		ft_memcpy_s(tmp + total, buf, n);
		tmp[total + n] = '\0';
		free(content);
		content = tmp;
		total += n;
		n = read(fd, buf, 4096);
	}
	return (content);
}
