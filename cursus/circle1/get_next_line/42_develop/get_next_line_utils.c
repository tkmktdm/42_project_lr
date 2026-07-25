/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: htakumi <htakumi@student.42tokyo.jp>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/07 19:52:31 by hibitakumi        #+#    #+#             */
/*   Updated: 2026/07/25 13:25:16 by htakumi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*grow_buf(char *left, char *buf, int bytes, t_leftover *info)
{
	size_t	i;
	size_t	new_capacity;
	char	*new_left;

	new_capacity = (info->len + (size_t)bytes) * 2;
	new_left = malloc(new_capacity);
	if (!new_left)
	{
		free(left);
		info->len = 0;
		info->capacity = 0;
		return (NULL);
	}
	i = -1;
	while (++i != info->len)
		new_left[i] = left[i];
	free(left);
	i = -1;
	while (++i != (size_t)bytes)
		new_left[info->len + i] = buf[i];
	new_left[info->len + i] = '\0';
	info->len += (size_t)bytes;
	info->capacity = new_capacity;
	return (new_left);
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

char	*fill_leftover(int fd, char *leftover)
{
	char		*buf;
	int			byte_num;
	t_leftover	info;

	info.len = 0;
	while (leftover && leftover[info.len] != '\0')
		info.len++;
	info.capacity = info.len + 1;
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
	free(buf);
	if (!buf || byte_num < 0)
	{
		free(leftover);
		return (NULL);
	}
	return (leftover);
}

char	*extract_line(char *leftover)
{
	char	*line;
	int		i;
	int		len;

	len = 0;
	while (leftover[len] != '\0' && leftover[len] != '\n')
		len++;
	if (leftover[len] == '\n')
		len++;
	line = malloc(sizeof(char) * (len + 1));
	if (!line)
		return (NULL);
	i = 0;
	while (leftover[i] != '\n' && leftover[i] != '\0')
	{
		line[i] = leftover[i];
		i++;
	}
	line[i] = leftover[i];
	if (leftover[i] == '\n')
		line[i + 1] = '\0';
	return (line);
}

char	*update_leftover(char *leftover)
{
	char	*p;
	char	*right;
	int		len;
	int		i;

	p = ft_strchr_gnl(leftover, '\n');
	if (p == NULL)
		return (NULL);
	p++;
	len = 0;
	while (p[len] != '\0')
		len++;
	if (len == 0)
		return (NULL);
	right = malloc(sizeof(char) * (len + 1));
	if (!right)
		return (NULL);
	i = 0;
	while (p[i] != '\0')
	{
		right[i] = p[i];
		i++;
	}
	right[i] = '\0';
	return (right);
}
