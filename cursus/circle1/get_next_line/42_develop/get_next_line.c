/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/07/08 20:10:15 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

static char	*append_buf(char *left, char *buf, int bytes, t_leftover *info)
{
	size_t	i;
	size_t	check_len;

	check_len = info->len + (size_t)bytes;
	if (check_len >= info->capacity)
		left = grow_buf(left, buf, (size_t)bytes, info);
	else
	{
		i = -1;
		while (++i != (size_t)bytes)
			left[info->len + i] = buf[i];
		left[info->len + i] = '\0';
		info->len += i;
	}
	return (left);
}

static char	*fill_leftover(int fd, char *leftover)
{
	char		*buf;
	int			byte_num;
	t_leftover	info;

	info.len = ft_strlen(leftover);
	info.capacity = ft_strlen(leftover) + 1;
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	byte_num = 0;
	while (buf && (leftover == NULL || ft_strchr_gnl(leftover, '\n') == NULL))
	{
		byte_num = read(fd, buf, BUFFER_SIZE);
		if (byte_num <= 0)
			break ;
		buf[byte_num] = '\0';
		leftover = append_buf(leftover, buf, byte_num, &info);
	}
	if (!buf || byte_num < 0)
	{
		free(buf);
		free(leftover);
		return (NULL);
	}
	free(buf);
	return (leftover);
}

char	*get_next_line(int fd)
{
	static char	*leftover = NULL;
	char		*line;
	char		*new_g_leftover;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	leftover = fill_leftover(fd, leftover);
	if (leftover == NULL || leftover[0] == '\0')
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	line = extract_line(leftover);
	if (!line)
	{
		free(leftover);
		leftover = NULL;
		return (NULL);
	}
	new_g_leftover = update_leftover(leftover);
	free(leftover);
	leftover = new_g_leftover;
	return (line);
}
